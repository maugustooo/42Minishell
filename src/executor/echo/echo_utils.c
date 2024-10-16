/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:11:25 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/15 13:39:58 by maugusto         ###   ########.fr       */
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

int	check_input2(t_token *token, t_mini *mini, t_token *file, t_token *temp)
{
	int	output_return;

	mini->echo_flag = true;
	output_return = output(token, mini, file, temp->type);
	if (output_return == 0)
	{
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_PERMS), temp->next->text);
		mini->return_code = 0;
		return (1);
	}
	else if (output_return == 2)
	{
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_ECHO_RED));
		mini->return_code = 2;
		return (1);
	}
	return (1);
}

int	check_input(t_token *token, t_mini *mini)
{
	t_token	*temp;
	t_token	*file;
	int		output_return;

	output_return = 0;
	temp = token;
	file = ft_finde_file(token);
	while (temp && temp->type != PIPE)
	{
		if ((temp->type == OUTPUT || temp->type == APPEND)
			&& !ft_find_c('"', temp->text) && !ft_find_c('\'', temp->text))
			return (check_input2(token, mini, file, temp));
		if (temp->type == HERE && !ft_find_c('"', temp->text)
			&& !ft_find_c('\'', temp->text))
			heredoc(token, file);
		temp = temp->next;
	}
	return (0);
}

int	check_valid_n_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] && str[i] == 'n')
			i++;
		return (str[i] == '\0');
	}
	return (0);
}

int	handle_n_flag(t_token **next)
{
	int	n_flag;

	n_flag = 0;
	while ((*next) && (ft_strncmp((*next)->text, "-n", 2) == 0)
		&& check_valid_n_flag((*next)->text))
	{
		n_flag++;
		(*next) = (*next)->next;
	}
	return (n_flag);
}
