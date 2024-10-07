/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:24:45 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/07 12:48:00 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_node(t_token **token)
{
	t_token	*current;

	current = *token;
	if (!token || !(*token))
		return ;
	if (current->prev)
		current->prev->next = current->next;
	if (current->next)
		current->next->prev = current->prev;
	*token = current->next;
	free(current->text);
	free(current);
}


void	add_token(t_mini *mini, char *start, int len, t_splited_data *data)
{
	if (mini->splited[data->index])
		free(mini->splited[data->index]);
	mini->splited[data->index] = ft_strndup(start, len);
}