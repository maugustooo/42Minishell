#include "minishell.h"

int output(t_token *token, t_mini *mini, t_token *last, int type)
{
	int fd;
	char *file;

	fd = 0;
	if (last->type == ARG || last->type == FILE || last->type == NOT_FILE)
		file = last->text;
	else
		ft_printf(Error_Msg(ERROR_ARG_ECHO));
	if (type == OUTPUT)
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

void	print_echo(t_token *next, t_mini *mini, int *first)
{
	int n_flag;

	n_flag = 0;
	while (next && (ft_strncmp(next->text, "-n", 2) == 0)
		&& check_valid_n_flag(next->text))
	{
		n_flag++;
    	next = next->next;
	}
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
        if (*first)
            ft_printf(" ");
        ft_printf("%s", next->text);
        *first = 1;
		next = next->next;
	}
	if (n_flag == 0)
        ft_printf("\n");
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
			mini->return_code = 1;
			return ;
		}
	}
	else
		ft_printf("\n");
	mini->return_code = 0;
}
