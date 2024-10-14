/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:10:34 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/14 13:52:38 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str)
{
	int		len;
	char	*new_str;

	len = strlen(str);
	if ((str[0] == '"' && str[len - 1] == '"') || (str[0] == '\''
			&& str[len - 1] == '\''))
	{
		new_str = malloc(len - 1);
		if (!new_str)
			return (NULL);
		ft_strncpy(new_str, str + 1, len - 2);
		new_str[len - 2] = '\0';
		return (new_str);
	}
	return (str);
}

void	move_left(char **args, int start_index)
{
	int	i;

	i = start_index;
	while (args[i + 1])
	{
		args[i] = args[i + 1];
		i++;
	}
	args[i] = NULL;
}

void	handle_heredoc(char ***args, int *i, t_mini *mini)
{
	char	buffer[1024];
	int		bytes_read;
	char	*delimiter;
	int		pipefd[2];

	mini->redirect = 1;
	pipe(pipefd);
	delimiter = (*args)[*i + 1];
	signal(SIGINT, handle_sigint_heredoc);
	while (1)
	{
		ft_printf("> ");
		bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		if (condition_hereoc(buffer, delimiter))
			break ;
		ft_printf_fd(pipefd[1], buffer);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	move_left_heredoc((*args), *i);
}

int	handle_input(char ***args, int *i, t_mini *mini)
{
	char	*filename;
	char	*original_filename;

	mini->redirect = 1;
	original_filename = (*args)[*i];
	filename = remove_quotes((*args)[*i]);
	if (!filename)
		return (0);
	mini->fd_in = open(filename, O_RDONLY);
	if (mini->fd_in < 0)
	{
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_NFILE), filename);
		move_left((*args), *i - 1);
		move_left((*args), *i - 1);
		return (free(filename), 0);
	}
	dup2(mini->fd_in, STDIN_FILENO);
	close(mini->fd_in);
	(*args)[*i] = filename;
	if (filename != original_filename)
		free(original_filename);
	move_left((*args), *i - 1);
	move_left((*args), *i -1);
	(*i)--;
	return (1);
}

int	handle_output(char ***args, int	*i, t_mini *mini)
{
	int	fd_out;

	fd_out = 0;
	mini->redirect = 1;
	if (ft_strcmp((*args)[*i], ">") == 0)
		fd_out = open((*args)[*i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp((*args)[*i], ">>") == 0)
		fd_out = open((*args)[*i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
		return (0);
	dup2(fd_out, STDOUT_FILENO);
	if (fd_out)
		close(fd_out);
	move_left((*args), *i);
	move_left((*args), *i);
	return (1);
}
