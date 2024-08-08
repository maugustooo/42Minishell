/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:36:43 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/08 14:09:44 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_unset(t_token *token, t_mini *mini)
{
	int		i;
	bool	found;
	char	**key;

	i = 0;
	found = false;
	while(mini->penv[i])
	{
		key = ft_split(mini->penv[i], '=');
		if (ft_strcmp(key[0],token->next->text) == 0)
		{
			found = true;
			break;
		}
		i++;
	}
	if(found == true)
	{
		mini->penv[i] = NULL;
	}
}
