/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 08:58:30 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/07 12:23:44 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_segment_iteration(t_token **temp, t_mini *mini,
	t_pipe_info *pipe_info)
{
	t_token	*start;
	int		pipefd[2];
	int		pid;

	mini->is_pipe = 2;
	start = *temp;
	if ((*temp)->next)
		check_pipes(mini, temp);
	if (mini->is_pipe == 1)
		pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		if (setup_pipes(pipe_info->fd_in, pipefd, start, mini))
		{
			freethem(temp, mini);
			free_things(mini);
			exit(mini->return_code);
		}
	}
	else
	{
		pipe_info->child_pids[(*pipe_info->pid_count)++] = pid;
		handle_parent_process(pipefd, pipe_info->fd_in, mini, temp);
	}
}

void	wait_for_children(pid_t *child_pids, int pid_count, t_mini *mini)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (i++ < pid_count)
	{
		waitpid(child_pids[i], &status, 0);
		if ((i == pid_count -1) && WIFEXITED(status))
			mini->return_code = WEXITSTATUS(status);
	}
}
