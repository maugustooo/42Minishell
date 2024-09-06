#include"minishell.h"

static void handle_parent_process(int pid, int pipefd[2], int *fd_in, int is_pipe, t_token **temp)
{
	(void)pid;
    if (is_pipe)
    {
        close(pipefd[1]);
        *fd_in = pipefd[0];
    }
	if(is_pipe == 2 || !is_pipe)
		*temp = (*temp)->next;
	else
		*temp = (*temp)->next->next;
}

static void execute_command(t_token *start, t_token *end, t_mini *mini)
{
    char **args;
    int i;
    char *cmd_path;

    i = 0;
    args = ft_calloc(mini->token_count + 1, sizeof(char *));
	if(start == end)
		args[i++] = start->text;
    while (start != end)
    {
		args[i++] = start->text;
        start = start->next;
    }
	if(start->text != args[i - 1])
    	args[i++] = start->text;
    args[++i] = NULL;
    cmd_path = ft_strjoin(CMD_PATH, args[0]);
    if (execve(cmd_path, args, mini->penv) == -1)
    {
        mini->return_code = 127;
        perror("execve");
    }
    free(cmd_path);
	exit(0);
}

static void setup_pipes(int *fd_in, int pipefd[2], int is_pipe, t_token *start, t_token **temp, t_mini *mini)
{
    if (*fd_in != 0)
    {
        dup2(*fd_in, STDIN_FILENO);
        close(*fd_in);
    }
    if (is_pipe == 1)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
    }
	if (is_pipe == 1)
		close(pipefd[0]);
	if(is_built_in(start))
	{
		handle_built_ins(&start, mini);
		exit(0);
	}
	else
		execute_command(start, *temp, mini);
}

static void process_pipe_segment(t_token **temp, int *fd_in, 
	int *pid, t_mini *mini, t_token **token)
{
    int pipefd[2];
    t_token *start;
    int is_pipe;

	is_pipe = 0;
	while (temp && *temp)
	{
		is_pipe = 2;
		start = *temp;
		if((*temp)->next)
		{
			check_pipes(&is_pipe, temp);
		}
		if (is_pipe == 1)
			pipe(pipefd);
		*pid = fork();
		if (*pid == 0)
			setup_pipes(fd_in, pipefd, is_pipe, start, temp, mini);
		else
			handle_parent_process(*pid, pipefd, fd_in, is_pipe, temp);
		if(mini->return_code == 127)
			handle_exit(token, mini);
	}
	ft_printf("Adoro bater em sem abrigos");
	freethem(token, mini);
    waitpid(*pid, NULL, 0);
}

void pipes(t_token **token, t_mini *mini, int pid)
{
    int fd_in;
    t_token *temp;

	temp = *token;
	fd_in = 0;
	if (!mini->final_pipe)
        	process_pipe_segment(&temp, &fd_in, &pid, mini, token);
	else
	{
		mini->return_code = 0;
		ft_printf(Error_Msg(ERROR_PIPE));
		mini->final_pipe = 0;
	}
}
