/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:20:31 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/15 15:45:55 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int return_dup_files(t_token **token)
{
	return (((*token)->next->type == FILE
			|| (*token)->next->type == NFILE || (*token)->next->type == INPUT
			|| (*token)->type == INPUT || (*token)->type == HERE
			|| (*token)->prev->type == HERE) && ((*token)->next
			&& (*token)->next->type != PIPE));
}

int	return_next(t_token *tmp)
{
	return((!ft_strcmp(tmp->text, "<<") && !tmp->next)
			|| ((!ft_strcmp(tmp->text, ">")
			|| !ft_strcmp(tmp->text, ">>") || !ft_strcmp(tmp->text, "<"))
			&& !tmp->next));	
}