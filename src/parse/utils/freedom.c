/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:05:26 by maugusto          #+#    #+#             */
/*   Updated: 2024/08/13 14:00:08 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_things(t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->penv)
	{
		while (mini->penv[i])
		{
			free(mini->penv[i]);
			i++;
		}
		free(mini->penv);
		mini->penv = NULL;
	}
	if(mini->prev_dir)
	{
		free(mini->prev_dir);
		mini->prev_dir = NULL;
	}
}

/**
 * @brief free the params
 * 
 * @param token the list of tokens
 * @param splited the tokens splited
 */
void	freethem(t_token **token, t_mini *mini)
{
	int	i;

	i = 0;
	if(token)
		ft_tokenclear(token);
	if(mini->splited)
	{
		while (mini->splited[i])
			free(mini->splited[i++]);
		free(mini->splited);
		mini->splited = NULL;
	}
}
