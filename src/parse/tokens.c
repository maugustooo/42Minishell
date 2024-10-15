/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:04:18 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/15 09:10:18 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Set the values type of the node
 * 
 * @param token the current node to set the type
 */
int	set_type(char *text)
{
	int	type;

	type = 0;
	if (ft_strcmp("<", text) == 0)
		type = INPUT;
	else if (ft_find_c('>', text) == 1)
		type = OUTPUT;
	else if (ft_find_c('>', text) == 1 && ft_find_c('>', text + 1) == 1)
		type = APPEND;
	else if (ft_strcmp("<<", text) == 0)
		type = DELIMITER;
	else if (ft_strcmp(text, "|") == 0)
		type = PIPE;
	else
		type = ARG;
	return (type);
}

int	condition(t_token **tok, t_mini *mini)
{
	if (((*tok)->text[0] == '<' && ((*tok)->text[1])
			&& (*tok)->text[1] != '<') || ((*tok)->text[0] == '\"'
			&& (*tok)->text[1] == '<' && (*tok)->text[2]))
	{
		if (check_file_token(*tok, 1, mini) == 1)
			return (1);
		else if (check_file_token(*tok, 1, mini) == 2)
		{
			(*tok)->type = NO_PERM;
			return (3);
		}
		else
			return (0);
	}
	if ((return_redirect((*tok)->prev) || (*tok)->prev->type == FILE)
		&& check_file_token(*tok, 0, mini)
		&& (*tok)->type != OUTPUT && (*tok)->type != INPUT
		&& (*tok)->type != APPEND && (*tok)->type != PIPE)
		return (1);
	else if (return_redirect((*tok)->prev) && !check_file_token(*tok, 0, mini)
		&& (*tok)->type != OUTPUT && (*tok)->type != INPUT
		&& (*tok)->type != APPEND && (*tok)->type != PIPE)
		return (0);
	return (2);
}

/**
 * @brief init the current node of the list
 * 
 * @param text the word splited
 * @return the node inited
 */
static void	init_token(t_token **token, char *text, t_mini *mini)
{
	int		type;
	char	cwd[1024];
	char	*file;
	char	*cwd_slash;

	file = NULL;
	cwd_slash = NULL;
	type = set_type(text);
	ft_tokenadd_back(token, ft_newnode(type, text));
	if ((*token)->next)
		(*token) = (*token)->next;
	if ((*token) && (*token)->prev)
	{
		getcwd(cwd, sizeof(cwd));
		cwd_slash = ft_strjoin(cwd, "/");
		file = ft_strjoin(cwd_slash, (*token)->text);
		free(cwd_slash);
		if (condition(token, mini) == 1)
			(*token)->type = FILE;
		else if (!condition(token, mini))
			(*token)->type = NOT_FILE;
		if ((*token)->prev->type == PIPE && ft_strcmp((*token)->text, "|") != 0)
			(*token)->type = CMD;
		free(file);
	}
}

void	get_tokens(t_token **token, t_mini *mini)
{
	int	i;

	i = 0;
	ft_tokenadd_back(token, ft_newnode(CMD, mini->splited[i]));
	while (mini->splited[++i])
		init_token(token, mini->splited[i], mini);
	while ((*token)->prev)
		(*token) = (*token)->prev;
}

void	remove_dup_files(t_token **token)
{
	while ((*token)->next)
	{
		if ((*token)->type == INPUT && (*token)->next)
		{
			(*token) = (*token)->next;
			while ((*token)->next && ((*token)->type == FILE
					|| (*token)->type == NOT_FILE
					|| (*token)->next->type == INPUT
					|| (*token)->type == INPUT))
			{
				if ((*token)->next->type == FILE
					|| (*token)->next->type == NOT_FILE
					|| (*token)->next->type == INPUT
					|| (*token)->type == INPUT)
					remove_node(token);
				else
					break ;
			}
		}
		if ((*token)->next)
			(*token) = (*token)->next;
	}
	while ((*token)->prev)
		(*token) = (*token)->prev;
}
