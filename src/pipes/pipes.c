#include"minishell.h"

void	handle_parent_process(int pipefd[2], int *fd_in, t_mini *mini, t_token **temp)
{
    if (mini->is_pipe)
    {
        close(pipefd[1]);
        *fd_in = pipefd[0];
    }
	if (mini->is_pipe == 2 || !mini->is_pipe)
		*temp = (*temp)->next;
	else
		*temp = (*temp)->next->next;
}

void	setup_pipes(int *fd_in, int pipefd[2], t_token *start, t_token **temp, t_mini *mini)
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
	}
	close(pipefd[0]);
	if (is_built_in(start))
	{
		handle_built_ins(&start, mini);
		freethem(temp, mini);
		free_things(mini);
		exit(mini->return_code);
	}
	else
	{
		mini->return_code = handle_cmd_pipe(&start, mini);
		exit(mini->return_code);
	}
}

void process_pipe_segment(t_token **temp, int *fd_in, t_mini *mini)
{
    pid_t child_pids[1024];
    int pid_count;
    t_pipe_info pipe_info;

	ft_bzero(child_pids, sizeof(pid_t) * 1024);
	pid_count = 0;
    pipe_info.fd_in = fd_in;
    pipe_info.pid_count = &pid_count;
    pipe_info.child_pids = child_pids;
    while (temp && *temp)
        process_segment_iteration(temp, mini, &pipe_info);
    wait_for_children(child_pids, pid_count, mini);
}

void pipes(t_token **token, t_mini *mini)
{
    int fd_in;
    t_token *temp;

	temp = *token;
	fd_in = 0;
	if (!mini->final_pipe)
        	process_pipe_segment(&temp, &fd_in, mini);
	else
	{
		mini->return_code = 0;
		ft_printf(Error_Msg(ERROR_PIPE));
		mini->final_pipe = 0;
	}
}