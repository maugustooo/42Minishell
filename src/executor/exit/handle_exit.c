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
	while ((*token)->text[i])
	{
		if ((*token)->text[i] < '0' || (*token)->text[i] > '9')
			return(false);
		i++;
	}
	return(true);
}

/**
 * @brief Handles the exit command
*/
void    handle_exit(t_token **token, t_mini *mini)
{
	// int n_token;

	// n_token = 0;
	// if((*token)->next)
	// {
	// 	n_token = count_tokens(mini->line, mini);
	// 	if(n_token > 2)
	// 		ft_printf(Error_Msg(ERROR_TARG), (*token)->text);
	// 	else
	// 	{
	// 		if(strnum(token))
	// 			ft_printf(Error_Msg(ERROR_NUMARG), (*token)->text);
	// 		else
	// 			mini->return_code = ft_atoi((*token)->text);
	// 	}
	// }
	free_things(mini);
	freethem(token, mini);
    exit(mini->return_code);
}

/**@}*/