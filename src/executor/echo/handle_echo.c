#include "minishell.h"

static void heredoc(t_token *token, t_token *last)
{
    char *line;
    int fd;
    char *delimiter;

    delimiter = token->next->text;
    fd = open(last->text, O_WRONLY | O_CREAT | O_TRUNC, 0644);    
    if (fd < 0)
        return ;
    while (1)
    {
        line = readline("> ");
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        ft_putendl_fd(line, fd);
        free(line);
    }
    close(fd);
}

static int input(t_token *token, t_mini *mini, t_token *last, int type)
{
	int fd;
	char *file;

	fd = 0;
	if (last->type == ARG || last->type == FILE || last->type == NOT_FILE)
		file = last->text;
	else
		ft_printf(Error_Msg(ERROR_ARG_ECHO));
	if (type == INPUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC);
	else if (type == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND);
	if(!check_file_perms(last))
		return (0);
	if (fd)
		while (token && token->type == ARG)
		{
			if (token->next->type == ARG && ft_strcmp(token->text, "-n") != 0)
				ft_printf_fd(fd, "%s ", token->text);
			else if (!mini->echo_flag)
				ft_printf_fd(fd, "%s\n", token->text);
			else if (token->type == ARG && ft_strcmp(token->text, "-n") != 0)
				ft_printf_fd(fd, token->text);
			token = token->next;
		}
	else
		check_access(token->text);
	return (1);
}

static int check_input(t_token *token, t_mini *mini)
{
	t_token *temp;
	t_token *last;

	temp = token;
	last = ft_tokenlast(token);
	while (temp && temp->type != PIPE)
	{
		if ((temp->type == INPUT || temp->type == APPEND) && !ft_find_c('"', temp->text) && !ft_find_c('\'', temp->text))
		{
			mini->echo_flag = true;
			if(!input(token, mini, last, temp->type))
				return(2);
			return (1);
		}
		if (temp->type == DELIMITER && !ft_find_c('"', temp->text) && !ft_find_c('\'', temp->text))
			heredoc(token, last);
		temp = temp->next;
	}
	return (0);
}

static void print_echo(t_token *next, t_mini *mini, int *first)
{
	while (next && next->type != PIPE)
	{
		if(check_redirect(&next) == 1)
			continue ;
		else if(check_redirect(&next) == 2)
		{
			mini->return_code = 1;
			ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_NFILE), next->text);
			break;
		}
		expander(&next, mini);
		if (next && *first == 2 && ft_strcmp(next->text, "-n") != 0)
		{
			ft_printf("%s", next->text);
			*first = 2;
		}
		if (next && !mini->echo_flag)
			ft_printf("%s", next->text);
		else if (next->next && !*first)
		{
			next = next->next;
			if (ft_strcmp(next->text, "-n") != 0)
				ft_printf("%s", next->text);
			*first = 2;
		}
		if (next->next && next->next->type != PIPE)
		{
			if (ft_strcmp(next->text, "-n") != 0)
				ft_printf(" ");
		}
		next = next->next;
	}
}

void	handle_echo(t_token **token, t_mini *mini)
{
	int first;
	t_token *temp;

	temp = *token;
	first = 0;
	if (temp->next)
	{
		temp = temp->next;
		if (check_input(temp, mini) == 0)
			print_echo(temp, mini, &first);
		else if (check_input(temp, mini) == 2)
		{
			//TODO:ISTO ESTA A PRINTAR NO TERMINAL TAMBEM LOL
			ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_PERMS), (*token)->text);
			free_child(token, mini, NULL);
			mini->return_code = 1;
			return ;
		}
		if (mini->echo_flag == false)
				ft_printf("\n");
		mini->echo_flag = false;
	}
	else
		ft_printf("\n");
	mini->return_code = 0;
}
