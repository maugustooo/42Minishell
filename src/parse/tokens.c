/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:04:18 by maugusto          #+#    #+#             */
/*   Updated: 2024/09/27 17:32:48 by maugusto         ###   ########.fr       */
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
	if (ft_find_c('<', text) == 1)
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

int	condition(t_token **token, char *file, t_mini *mini)
{
	if (((*token)->prev->type == OUTPUT
			|| (*token)->prev->type == INPUT
			|| (*token)->prev->type == APPEND) && check_file_token(token, file, mini)
		&& (*token)->type != OUTPUT && (*token)->type != INPUT
		&& (*token)->type != APPEND && (*token)->type != PIPE)
		return (1);
	else if (((*token)->prev->type == OUTPUT
			|| (*token)->prev->type == INPUT
			|| (*token)->prev->type == APPEND) && !check_file_token(token, file, mini)
		&& (*token)->type != OUTPUT && (*token)->type != INPUT
		&& (*token)->type != APPEND && (*token)->type != PIPE)
		return (0);
	else
		return(2);
	
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
		if (condition(token, file, mini) == 1)
			(*token)->type = FILE;
		else if(!condition(token, file, mini))
			(*token)->type = NOT_FILE;
		if((*token)->prev->type == PIPE)
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
