/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:01:56 by gude-jes          #+#    #+#             */
/*   Updated: 2024/11/04 10:01:56 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_segment_iteration(t_token **temp, t_mini *mini,
	t_pipe_info *pipe_info)
{
	t_token	*start;
	int		pipefd[2];

	mini->is_pipe = 2;
	start = *temp;
	if ((*temp)->next)
		check_pipes(mini, temp);
	if (mini->is_pipe == 1)
		if (pipe(pipefd) == -1)
			handle_exit(temp, mini);
	pipe_info->pid = fork();
	signal(SIGINT, handle_sigint2);
	if (pipe_info->pid == 0)
	{
		if (setup_pipes(pipe_info->fd_in, pipefd, start, mini))
		{
			free_child(temp, mini, NULL);
			exit(mini->return_code);
		}
	}
	else
	{
		pipe_info->child_pids[(*pipe_info->pid_count)++] = pipe_info->pid;
		handle_parent_process(pipefd, pipe_info->fd_in, mini, temp);
	}
}

void	wait_for_children(pid_t *child_pids, int pid_count, t_mini *mini)
{
	int	status;
	int	i;

	status = 0;
	i = pid_count;
	while (i-- > 0)
	{
		waitpid(child_pids[i], &status, 0);
		if ((i == pid_count -1) && WIFEXITED(status))
			mini->return_code = WEXITSTATUS(status);
	}
}
