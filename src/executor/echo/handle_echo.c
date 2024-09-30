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
