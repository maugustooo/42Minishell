/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:36:54 by maugusto          #+#    #+#             */
/*   Updated: 2024/09/23 14:55:32 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_nodes(t_token *token)
{
	t_token *temp;
	int i;

	i = 0;
	temp = token;
	while (temp)
	{
		i++ ;
		temp = temp->next;
	}
	return (i);
}

int	check_file_token(char *file)
{
	struct stat	path_stat;

	if (stat(file, &path_stat) == -1)
		return (0);
	if (S_ISREG(path_stat.st_mode))
	{
		if (access(file, R_OK) == 0)
			return (1);
		else
			return(0);
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_ISDIR), file);
		return(0);
	}
	else
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_CD), file);
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
		temp = temp->next;
	}
}