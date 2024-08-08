/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:04:18 by maugusto          #+#    #+#             */
/*   Updated: 2024/08/05 12:45:25 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Set the values type of the node
 * 
 * @param token the current node to set the type
 */
int set_type(char	*text)
{
	int type;

	type = 0;
	if(ft_strncmp(text, "<", ft_strlen(text)) == 0)
		type = INPUT;
	else if(ft_strncmp(text, ">", ft_strlen(text)) == 0)
		type = OUTPUT;
	else if(ft_strncmp(text, ">>", ft_strlen(text)) == 0)
		type = APPEND;
	else if(ft_strncmp(text, "<<", ft_strlen(text)) == 0)
		type = DELIMITER;
	else if(ft_strncmp(text, "|", ft_strlen(text)) == 0)
		type = PIPE;
	else
		type = ARG;
	return(type);
}

/**
 * @brief init the current node of the list
 * 
 * @param text the word splited
 * @return the node inited
 */
static void init_token(t_token **token, char *text)
{
	int type;

	type = 0;
	type = set_type(text);
	ft_tokenadd_back(token, ft_newnode(type, text));
}

/**
 * @brief Get the tokens and returns them
 * 
 * @param mini The struct of the minishell
 * @return List of tokens
 */
void get_tokens(t_token	**token, char ***splited)
{
	int i;	

	i = 0;
	ft_tokenadd_back(token, ft_newnode(CMD, (*splited)[i]));
	while ((*splited)[++i])
		init_token(token,  (*splited)[i]);
}
