/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:04:18 by maugusto          #+#    #+#             */
/*   Updated: 2024/07/29 15:47:52 by maugusto         ###   ########.fr       */
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
	if(ft_strncmp(token->line, "<", ft_strlen(token->line)))
		token->type = INPUT;
	else if(ft_strncmp(token->line, ">", ft_strlen(token->line)))
		token->type = OUTPUT;
	else if(ft_strncmp(token->line, ">>", ft_strlen(token->line)))
		token->type = APPEND;
	else if(ft_strncmp(token->line, "<<", ft_strlen(token->line)))
		token->type = DELIMITER;
	else if(ft_strncmp(token->line, "|", ft_strlen(token->line)))
		token->type = PIPE;
	else
		token->type = ARG;
}

/**
 * @brief init the current node of the list
 * 
 * @param line the word splited
 * @return the node inited
 */
static t_token *init_token(char *line)
{
	t_token *token;

	token = ft_calloc(1, sizeof(t_token));
	if(!token)
		return(NULL);
	token->line = line;
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