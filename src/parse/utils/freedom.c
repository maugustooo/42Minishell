/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:05:26 by maugusto          #+#    #+#             */
/*   Updated: 2024/08/20 11:26:28 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_things(t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->penv)
	{
		free_penv(mini);
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
