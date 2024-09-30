/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:36:54 by maugusto          #+#    #+#             */
/*   Updated: 2024/09/30 12:31:34 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_nodes(t_token *token)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = token;
	while (temp)
	{
		i++ ;
		temp = temp->next;
	}
	return (i);
}

int	check_file_token(t_token **token, char *file, t_mini *mini)
{
	struct stat	path_stat;
	t_token **temp;
	
	(void)file;
	temp = token;
	if(ft_find_c('\"', (*temp)->text))
		expander(temp, mini);
	if (stat((*temp)->text, &path_stat) == -1)
		return (0);
	if (S_ISREG(path_stat.st_mode))
	{
		if (access((*temp)->text, R_OK) == 0)
			return (1);
		else
			return (0);
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_ISDIR), (*temp)->text);
		return (0);
	}
	else
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_CD), (*temp)->text);
	return (0);
}

t_token	*ft_tokenlast_redirect(t_token *token)
{
	while (token)
	{
		if (token->next && (token->type  == INPUT || token->type  == OUTPUT
			|| token->type  == APPEND))
		{
			if(token->next->type == FILE && !token->next->next)
				return (token);
		}
		token = token->next;
	}
	return (token);
}

void count_redirections(t_token *token, t_mini *mini)
{
	t_token *temp;
	int i;

	i = 0;
	temp = token;
	while (temp)
	{
		if(temp->type == INPUT)
			mini->input_count++;
		if(temp->type == OUTPUT)
			mini->output_count++;
		if(temp->type == APPEND)
			mini->append_count++;
		if(temp->type == FILE)
			mini->file_count++;
		temp = temp->next;
	}
}

t_token *ft_finde_file(t_token *token)
{
	t_token *temp;

	temp = token;
	while (temp)
	{
		if (temp->type == FILE || temp->type == NOT_FILE)
			return (temp);
		temp = temp->next;
	}
	return (temp);
}
