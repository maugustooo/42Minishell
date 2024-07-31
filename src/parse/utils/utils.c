/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:05:35 by maugusto          #+#    #+#             */
/*   Updated: 2024/07/31 18:21:06 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * @brief Clear the list
 * 
 * @param token The list
 */
void	ft_tokenclear(t_token **token)
{
	t_token	*tmp;

	if (!token || !*token)
		return ;
	while (*token)
	{
		tmp = (*token)->next;
		free((*token)->text);
		free(*token);
		*token = tmp;
	}
}
/**
 * @brief create a new node to the list
 * 
 * @param type data in node
 * @param text data in node
 * @return new node 
 */
t_token	*ft_newnode(int type, char *text)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->text = text;
	token->next = NULL;
	return (token);
}
/**
 * @brief will add a new node 
 * 
 * @param token the list
 * @param new the new node
 */
void	ft_tokenadd_back(t_token **token, t_token *new)
{
	t_token	*last;

	if (token)
	{
		if (*token)
		{
			last = ft_tokenlast(*token);
			last->next = new;
		}
		else
			*token = new;
	}
}
/**
 * @brief return the last node
 * 
 * @param token list
 * @return last node 
 */
t_token	*ft_tokenlast(t_token *token)
{
	while (token)
	{
		if (!token->next)
			return (token);
		token = token->next;
	}
	return (token);
}