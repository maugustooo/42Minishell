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
	if((*token)->next->text[i] == '+' || (*token)->next->text[i] == '-')
		i++;
	while ((*token)->next->text[i])
	{
		if (ft_isdigit((*token)->next->text[i]))
			i++;
		else
			return(true);
	}
	return(false);
}

void	exit_code(t_token **token, t_mini *mini)
{
	int	code;

	code = ft_atoi((*token)->next->text);
	if (code > 256)
		code %= 256;
	else if (code == 256)
		code = 0;
	else if (code < 0)
		code = 256 - (code * -1);
	mini->return_code = code;
}

/**
 * @brief Handles the exit command
*/
void    handle_exit(t_token **token, t_mini *mini)
{
	int n_token;

	n_token = 0;
	if(token != NULL && *token != NULL)
	{
		if((*token)->next)
		{
			n_token = count_tokens(mini->line, mini);
			if(n_token > 2)
				ft_printf(Error_Msg(ERROR_TARG), (*token)->text);
			else
			{
				expander(token, mini);
				if(strnum(token))
					ft_printf(Error_Msg(ERROR_NUMARG), (*token)->text);
				else
					exit_code(token, mini);
			}
		}
	}
	free_things(mini);
	freethem(token, mini);
    exit(mini->return_code);
}

/**@}*/