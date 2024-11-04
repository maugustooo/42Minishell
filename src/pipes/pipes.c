/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:07:06 by gude-jes          #+#    #+#             */
/*   Updated: 2024/11/04 09:07:06 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_parent_process(int pipefd[2], int *fd_in, t_mini *mini,
		t_token **temp)
{
	if (mini->is_pipe == 1)
	{
		close(pipefd[1]);
		*fd_in = pipefd[0];
	}
	if (mini->is_pipe == 0 || mini->is_pipe == 2)
		close(*fd_in);
	if (mini->is_pipe == 2 || !mini->is_pipe)
		*temp = (*temp)->next;
	else
		*temp = (*temp)->next->next;
}

int	setup_pipes(int *fd_in, int pipefd[2], t_token *start, t_mini *mini)
{
	if (*fd_in != 0)
	{
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
	if (mini->is_pipe == 1)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
	}
	if (is_built_in(start))
	{
		handle_built_ins(&start, mini);
		return (1);
	}
	else
	{
		mini->return_code = handle_cmd_pipe(&start, mini);
		exit(mini->return_code);
	}
	return (0);
}

void	process_pipe_segment(t_token **temp, int *fd_in, t_mini *mini)
{
	pid_t		child_pids[1024];
	int			pid_count;
	t_pipe_info	pipe_info;
	int			pid;

	ft_bzero(child_pids, sizeof(pid_t) * 1024);
	pid_count = 0;
	pid = 0;
	pipe_info.fd_in = fd_in;
	pipe_info.pid_count = &pid_count;
	pipe_info.child_pids = child_pids;
	pipe_info.pid = pid;
	count_redirections(*temp, mini);
	if (mini->here_count >= 1)
		heredoc_pipe(temp, mini);
	while (temp && *temp)
		process_segment_iteration(temp, mini, &pipe_info);
	wait_for_children(child_pids, pid_count, mini);
}

void	pipes(t_token **token, t_mini *mini)
{
	int		fd_in;
	t_token	*temp;

	temp = *token;
	fd_in = 0;
	if (!mini->final_pipe && mini->after_pipe)
		process_pipe_segment(&temp, &fd_in, mini);
	else
	{
		mini->return_code = 0;
		mini->final_pipe = 0;
	}
	dup2(mini->saved_stdin, STDIN_FILENO);
}
