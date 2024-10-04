/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 08:58:30 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/04 09:32:44 by gude-jes         ###   ########.fr       */
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
        setup_pipes(pipe_info->fd_in, pipefd, start, temp, mini);
    else
    {
        pipe_info->child_pids[(*pipe_info->pid_count)++] = pid;
        handle_parent_process(pipefd, pipe_info->fd_in, mini, temp);
    }
}

void	wait_for_children(pid_t *child_pids, int pid_count, t_mini *mini)
{
	int status;
	int	i;

	i = 0;
	while (i++ < pid_count)
	{
		waitpid(child_pids[i], &status, 0);
		if ((i == pid_count -1) &&  WIFEXITED(status))
			mini->return_code = WEXITSTATUS(status);
    }
}
