/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:45:18 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/03 12:36:27 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if ((*token)->text[i] == '+' || (*token)->text[i] == '-')
		i++;
	while ((*token)->text[i])
	{
		if (ft_isdigit((*token)->text[i]))
			i++;
		else
			return (true);
	}
	return (false);
}

void	exit_code(t_token **token, t_mini *mini)
{
	long long	code;

	code = ft_atoll((*token)->text);
	if (code > 9223372036854775807
		|| code < -9223372036854775807)
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_ENUM), (*token)->text);
		code = 2;
	}
	else
	{
		if (code > 256)
			code %= 256;
		else if (code == 256)
			code = 0;
		else if (code < 0)
			code = 256 - (code * -1);
	}
	mini->return_code = code;
}

void	handle_codes2(t_token **token, t_mini *mini)
{
	*token = (*token)->next;
	expander(token, mini);
	if (strnum(token))
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_NUMARG), (*token)->text);
		mini->return_code = 2;
	}
	else
		exit_code(token, mini);
}

void	handle_codes(t_token **token, t_mini *mini, int n_token)
{
	if (token != NULL && *token != NULL)
	{
		if ((*token)->next)
		{
			n_token = count_nodes(*token);
			if (n_token > 2 && !mini->pipe)
			{
				ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_TARG),
					(*token)->text);
				mini->return_code = 1;
			}
			else
				handle_codes2(token, mini);
		}
	}
}

/**
 * @brief Handles the exit command
*/
void	handle_exit(t_token **token, t_mini *mini)
{
	int	n_token;

	n_token = 0;
	handle_codes(token, mini, n_token);
	free_things(mini);
	freethem(token, mini);
	exit (mini->return_code);
}

/**@}*/