/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:41:20 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/03 12:41:55 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pipes(t_mini *mini, t_token **temp)
{
	mini->is_pipe = ((*temp)->next && strcmp((*temp)->next->text, "|") == 0);
	while ((*temp)->next && !mini->is_pipe)
	{
		*temp = (*temp)->next;
		mini->is_pipe = ((*temp)->next
				&& strcmp((*temp)->next->text, "|") == 0);
	}
}
