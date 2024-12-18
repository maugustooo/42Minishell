/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:07:13 by gude-jes          #+#    #+#             */
/*   Updated: 2024/11/04 10:06:30 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_left(char **args, int start_index)
{
	int	i;

	if (!args || start_index < 0)
		return ;
	i = start_index;
	if (args[i])
		free(args[i]);
	while (args[i + 1])
	{
		args[i] = args[i + 1];
		i++;
	}
	args[i] = NULL;
}

void	close_and_move_left(char **args, int *i, t_mini *mini, int pipefd[2])
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	move_left_heredoc(args, *i, mini);
}

void	handle_heredoc(char ***args, int *i, t_mini *mini)
{
	char	buffer[1024];
	int		bytes_read;
	char	*delimiter;
	int		pipefd[2];

	mini->redirect = 1;
	pipe(pipefd);
	signal(SIGINT, handle_sigint_heredoc);
	while (mini->here_count > 0)
	{
		delimiter = set_delimiter(*args, i, mini);
		ft_printf_fd(mini->saved_stdout, "> ");
		bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		if (condition_hereoc(buffer, delimiter))
		{
			mini->here_count--;
			move_left_heredoc((*args), *i, mini);
		}
		else if (strcmp(delimiter, last_delimiter(*args)) == 0)
			ft_printf_fd(pipefd[1], buffer);
	}
	close_and_move_left(*args, i, mini, pipefd);
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
		return (0);
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
	struct stat	path_stat;
	int			fd_out;

	fd_out = 0;
	mini->redirect = 1;
	if (ft_strcmp((*args)[*i], ">") == 0)
		fd_out = open((*args)[*i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp((*args)[*i], ">>") == 0)
		fd_out = open((*args)[*i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (stat((*args)[*i + 1], &path_stat) != -1
		&& access((*args)[*i + 1], W_OK) != 0)
		return (handle_permission_error(args, i, ERROR_PERMS), 0);
	if (fd_out == -1)
		return (handle_permission_error(args, i, ERROR_NFILE), 0);
	dup2(fd_out, STDOUT_FILENO);
	if (fd_out)
		close(fd_out);
	move_left((*args), *i);
	move_left((*args), *i);
	return (1);
}
