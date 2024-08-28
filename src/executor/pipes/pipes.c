#include"minishell.h"

static void handle_parent_process(int pid, int pipefd[2], int *fd_in, int is_pipe)
{
    waitpid(pid, NULL, 0);
    if (is_pipe)
    {
        close(pipefd[1]);
        *fd_in = pipefd[0];
    }
}

static void execute_command(t_token *start, t_token *end, t_mini *mini, t_token **token)
{
    char *args[256];
    int i = 0;

    while (start != end)
    {
        args[i++] = start->text;
        start = start->next;
    }
    args[i] = NULL;
    if(execvp(args[0], args) == -1)
    {
		mini->return_code = 0;
		perror("execvp");
	}
    handle_exit(token, mini);
}

static void setup_pipes(int *fd_in, int pipefd[2], int is_pipe)
{
    if (*fd_in != 0)
    {
        dup2(*fd_in, STDIN_FILENO);
        close(*fd_in);
    }
    if (is_pipe)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
    }
    if (is_pipe)
        close(pipefd[0]);
}

static void process_pipe_segment(t_token **temp, int *fd_in, 
	int *pid, t_mini *mini, t_token **token)
{
    int pipefd[2];
    t_token *start;
    int is_pipe;
	
	start = *temp;
	is_pipe = ((*temp)->next && strcmp((*temp)->next->text, "|") == 0);
    while ((*temp)->next && !is_pipe)
    {
        *temp = (*temp)->next;
        is_pipe = ((*temp)->next && strcmp((*temp)->next->text, "|") == 0);
    }
    if (is_pipe)
        pipe(pipefd);
    *pid = fork();
    if (*pid == 0)
    {
        setup_pipes(fd_in, pipefd, is_pipe);
        execute_command(start, (*temp)->next, mini, token);
    }
    else
    {
        handle_parent_process(*pid, pipefd, fd_in, is_pipe);
        *temp = is_pipe ? (*temp)->next->next : (*temp)->next;
    }
}

void pipes(t_token **token, t_mini *mini, int pid)
{
    int fd_in;
    t_token *temp;

	temp = *token;
	fd_in = 0;
	if (!mini->final_pipe)
    	while (temp)
        	process_pipe_segment(&temp, &fd_in, &pid, mini, token);
	else
	{
		mini->return_code = 0;
		ft_printf(Error_Msg(ERROR_PIPE));
		mini->final_pipe = 0;
	}
}
