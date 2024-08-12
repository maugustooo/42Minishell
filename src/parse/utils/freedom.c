/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:05:26 by maugusto          #+#    #+#             */
/*   Updated: 2024/08/12 15:38:28 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
		free(mini->splited);
	// if (mini->penv)
	// {
	// 	while (mini->penv[i])
	// 	{
	// 		free(mini->penv[i]);
	// 		i++;
	// 	}
	// 	free(mini->penv);
	// 	mini->penv = NULL;
	// }
}
