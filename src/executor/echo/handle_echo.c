#include "minishell.h"

static void handle_input(t_token *token)
{
	int fd;
	char *file;

	file = token->next->next->text;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd > 0)
		ft_printf_fd(fd, token->text);
}

static void print_echo(t_token **next, t_mini *mini)
{
	int first;

	first = 0;
	expander(next, mini);
	if(next && first == 2)
		{
			ft_printf("%s", (*next)->text);
			first = 2;
		}
	if (next && !mini->echo_flag)
			ft_printf("%s", (*next)->text);
	else if ((*next)->next && !first)
		{
			(*next) = (*next)->next;
			ft_printf("%s", (*next)->text);
			first = 2;
		}
	(*next) = (*next)->next;
	if(*next)
	{
		if(ft_strcmp((*next)->text, "-n") != 0)
			ft_printf(" ");
	}
}

void	handle_echo(t_token *next, t_mini *mini)
{
	if(next)
	{
		while (next)
		{
			if(next->next)
				if(next->next->type == INPUT)
				{
					handle_input(next);
					return ;
				}
			print_echo(&next, mini);
		}
		if(mini->echo_flag == false)
				ft_printf("\n");
		mini->echo_flag = false;
	}
	else
		ft_printf("\n");
	mini->return_code = 0;
}
