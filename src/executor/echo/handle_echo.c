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

static void input(t_token *token, t_mini *mini, t_token *last, int type)
{
	int fd;
	char *file;

	fd = 0;
	if (last->type == ARG)
		file = last->text;
	else
		ft_printf(Error_Msg(ERROR_ARG_ECHO), token->next->next->text);
	if (type == INPUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd)
		while (token && token->type == ARG)
		{
			if(token->next->type == ARG && ft_strcmp(token->text, "-n") != 0)
				ft_printf_fd(fd, "%s ", token->text);
			else if(!mini->echo_flag)
				ft_printf_fd(fd, "%s\n", token->text);
			else if(token->type == ARG && ft_strcmp(token->text, "-n") != 0)
				ft_printf_fd(fd, token->text);
			token = token->next;
		}
}

static int check_input(t_token *token, t_mini *mini)
{
	t_token *temp;
	t_token *last;

	temp = token;
	last = ft_tokenlast(token);
	while (temp)
	{
		if (temp->type == INPUT || temp->type == APPEND)
		{
			mini->echo_flag = true;
			input(token, mini, last, temp->type);
			return(1);
		}
		if(temp->type == DELIMITER)
			heredoc(token, last);
		temp = temp->next;
	}
	return(0);
}

static void print_echo(t_token *next, t_mini *mini, int *first)
{	
	while (next && next->type != PIPE)
	{
		expander(&next, mini);
		if(next->type == OUTPUT || next->type == FILE || next->type == NOT_FILE)
		{
			next = next->next;	
			continue ;
		}
		if(next && *first == 2 && ft_strcmp(next->text, "-n") != 0)
		{
			ft_printf("%s", next->text);
			*first = 2;
		}
		if (next && !mini->echo_flag)
			ft_printf("%s", next->text);
		else if (next->next && !*first)
		{
			next = next->next;
			if(ft_strcmp(next->text, "-n") != 0)
				ft_printf("%s", next->text);
			*first = 2;
		}
		if(next->next && next->next->type != PIPE) //VERIFICAR ISTO - PELO QUE VI, SO IMPRIMIA A MAIS COM PIPE NE?
		{
			if(ft_strcmp(next->text, "-n") != 0)
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
	if(temp->next)
	{
		temp = temp->next;
		if(!check_input(temp, mini))
			print_echo(temp, mini, &first);
		if (mini->echo_flag == false)
				ft_printf("\n");
		mini->echo_flag = false;
	}
	else
		ft_printf("\n");
	mini->return_code = 0;
}
