/**
 * @defgroup mandatory Mandatory
 * @{
 * @file handle_exit.c
 * @brief Handles the exit
*/

#include "minishell.h"

bool	strnum(t_token **token)
{
	int	i;

	i = 0;
	if((*token)->text[i] == '+' || (*token)->text[i] == '-')
		i++;
	while ((*token)->text[i])
	{
		if (ft_isdigit((*token)->text[i]))
			i++;
		else
			return(true);
	}
	return(false);
}

void	exit_code(t_token **token, t_mini *mini)
{
	int	code;

	code = ft_atoi((*token)->text);
	if (code > 256)
		code %= 256;
	else if (code == 256)
		code = 0;
	else if (code < 0)
		code = 256 - (code * -1);
	mini->return_code = code;
}

void	handle_codes(t_token **token, t_mini *mini, int n_token)
{
	if(token != NULL && *token != NULL)
	{
		if((*token)->next)
		{
			n_token = count_nodes(*token);
			if(n_token > 2)
			{
				ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_TARG), (*token)->text);
				mini->return_code = 1;
			}
			else
			{
				*token = (*token)->next;
				expander(token, mini);
				if(strnum(token))
				{
					ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_NUMARG), (*token)->text);
					mini->return_code = 2;
				}
				else
					exit_code(token, mini);
			}
		}
	}
}

/**
 * @brief Handles the exit command
*/
void    handle_exit(t_token **token, t_mini *mini)
{
	int n_token;

	n_token = 0;
	handle_codes(token, mini, n_token);
	//ft_printf("HANDLE_EXIT : %d\n", mini->return_code);
	free_things(mini);
	freethem(token, mini);
    exit(mini->return_code);
}

/**@}*/