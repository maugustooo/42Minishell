/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:04:18 by maugusto          #+#    #+#             */
/*   Updated: 2024/08/26 10:52:12 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Set the values type of the node
 * 
 * @param token the current node to set the type
 */
int set_type(char *text)
{
	int type;

	type = 0;
	if(ft_strcmp(text, "<") == 0)
		type = OUTPUT;
	else if(ft_strcmp(text, ">") == 0)
		type = INPUT;
	else if(ft_strcmp(text, ">>") == 0)
		type = APPEND;
	else if(ft_strcmp(text, "<<") == 0)
		type = DELIMITER;
	else if(ft_strcmp(text, "|") == 0)
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

// /**
//  * @brief Get the tokens and returns them
//  * 
//  * @param mini The struct of the minishell
//  * @return List of tokens
//  */
// void get_tokens(t_token **token, t_mini *mini)
// {
// 	int i;
// 	char **new_splitedd;
//     int j;

//     i = 0;
// 	j = 0;
//     ft_tokenadd_back(token, ft_newnode(CMD, mini->splited[i]));
//     while (mini->splited[++i]) 
// 	{
// 		new_splitedd = ft_split(mini->splited[i], '|');
//         if (new_splitedd) 
// 		{
//             j = 0;
// 			if(ft_find_c('|', new_splitedd[j]))
// 				ft_tokenadd_back(token, ft_newnode(PIPE, "|"));
//             while (new_splitedd[j]) 
// 			{
// 				if(j == 0)
//                 	ft_tokenadd_back(token, ft_newnode(CMD, new_splitedd[j]));
// 				else
// 					init_token(token,  new_splitedd[j]);
//                 j++;
//             }
//             free(new_splitedd);
//         }
//     }
// }

void    get_tokens(t_token  **token, t_mini *mini)
{
    int i;
    i = 0;
    ft_tokenadd_back(token, ft_newnode(CMD, mini->splited[i]));
    while (mini->splited[++i])
        init_token(token,  mini->splited[i]);
}
