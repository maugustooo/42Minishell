/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:36:43 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/07 12:02:05 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_unset(t_token *token, t_mini *mini)
{
	int		i;
	bool	found;

	i = 0;
	found = false;
	while(mini->penv[i])
	{
		if (mini->penv[i] == token->text)
		{
			found = true;
			break;
		}
		i++;
	}
	if(found == true)
	{
		mini->penv[i] == NULL;
	}
}
