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
 * @brief Set the values in the current node of the list
 * 
 * @param line the word splited  
 * @param mini The struct of the minishell
 * @param token the current node to set the values
 */
static void set_values(char *line, t_mini *mini, t_token *token)
{
	token->line = line;
	
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
	(*token)->type = CMD;
	(*token)->line = *splited;
	while (splited[++i])
	{
		next = get_next(token);
		*token = (*token)->next;
		set_values(splited[i], mini, token);
	}
	
}