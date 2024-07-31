/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:04:18 by maugusto          #+#    #+#             */
/*   Updated: 2024/07/31 09:30:54 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Set the values type of the node
 * 
 * @param token the current node to set the type
 */
static void *set_type(t_token *token)
{
	if(ft_strncmp(token->text, "<", ft_strlen(token->text)))
		token->type = INPUT;
	else if(ft_strncmp(token->text, ">", ft_strlen(token->text)))
		token->type = OUTPUT;
	else if(ft_strncmp(token->text, ">>", ft_strlen(token->text)))
		token->type = APPEND;
	else if(ft_strncmp(token->text, "<<", ft_strlen(token->text)))
		token->type = DELIMITER;
	else if(ft_strncmp(token->text, "|", ft_strlen(token->text)))
		token->type = PIPE;
	else
		token->type = ARG;
}

/**
 * @brief init the current node of the list
 * 
 * @param text the word splited
 * @return the node inited
 */
static t_token *init_token(char *text)
{
	t_token *token;

	token = ft_calloc(1, sizeof(t_token));
	if(!token)
		return(NULL);
	token->text = text;
	set_type(token);
	return(token);
}

/**
 * @brief Get the tokens and returns them
 * 
 * @param mini The struct of the minishell
 * @return List of tokens
 */
t_token **get_tokens(t_mini *mini)
{
	char	**splited;
	t_token **token;
	t_token	*next;
	int i;
	
	splited = ft_split(mini->line, ' ');
	i = 0;
	*token = init_token(splited[i]);
	(*token)->type = CMD;
	while (splited[++i])
	{
		next = init_token(splited[i]);
		(*token)->next = next;
		*token = (*token)->next;
	}
	return(token);
}