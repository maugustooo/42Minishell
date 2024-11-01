/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:11:25 by gude-jes          #+#    #+#             */
/*   Updated: 2024/11/01 16:03:02 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_token *token, t_token *last)
{
	char	*line;
	int		fd;
	char	*delimiter;

	delimiter = token->next->text;
	fd = open(last->text, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}

void	output2(t_token *token)
{
	int	first_arg;

	first_arg = 1;
	while (token && token->type != PIPE)
	{
		if (token->type != ARG)
		{
			token = token->next;
			continue ;
		}
		if (!first_arg)
			ft_printf_fd(STDOUT_FILENO, " ");
		ft_printf_fd(STDOUT_FILENO, "%s", token->text);
		first_arg = 0;
		token = token->next;
	}
	ft_printf_fd(STDOUT_FILENO, "\n");
}

void	check_input2(t_token *token, t_mini *mini)
{
	mini->echo_flag = true;
	output2(token);
	dup2(mini->saved_stdout, STDOUT_FILENO);
	close(mini->saved_stdout);
}

int	check_input(t_token *token, t_mini *mini)
{
	t_token	*temp;
	t_token	*file;
	int		return_value;

	return_value = 0;
	temp = token;
	while (temp && temp->type != PIPE)
	{
		file = ft_finde_file(temp);
		if ((temp->type == OUTPUT || temp->type == APPEND)
			&& !ft_find_c('"', temp->text) && !ft_find_c('\'', temp->text)
			&& mini->num_outs-- == 1)
		{
			check_input2(token, mini);
			return_value = 1;
		}
		if (temp->type == HERE && !ft_find_c('"', temp->text)
			&& !ft_find_c('\'', temp->text))
			heredoc(token, file);
		temp = temp->next;
	}
	return (return_value);
}
