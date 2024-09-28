#include"minishell.h"

static void handle_parent_process(int pipefd[2], int *fd_in, t_mini *mini, t_token **temp)
{
    if (mini->is_pipe)
    {
        close(pipefd[1]);
        *fd_in = pipefd[0];
    }
	if(mini->is_pipe == 2 || !mini->is_pipe)
		*temp = (*temp)->next;
	else
		*temp = (*temp)->next->next;
}

// static void execute_command(t_token *start, t_token *end, t_mini *mini)
// {
//     char **args;
//     int i;
//     char *cmd_path;

//     i = 0;
//     args = ft_calloc(mini->token_count + 1, sizeof(char *));
// 	if(start == end)
// 		args[i++] = start->text;
//     while (start != end)
//     {
// 		args[i++] = start->text;
//         start = start->next;
//     }
// 	if(start->text != args[i - 1])
//     	args[i++] = start->text;
//     args[++i] = NULL;
//     cmd_path = ft_strjoin(CMD_PATH, args[0]);
//     if (execve(cmd_path, args, mini->penv) == -1)
//     {
//         mini->return_code = 127;
//         perror("execve");
//     }
//     free(cmd_path);
// 	exit(0);
// }

static void setup_pipes(int *fd_in, int pipefd[2], t_token *start, t_token **temp, t_mini *mini)
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
	if (mini->is_pipe == 1)
		close(pipefd[0]);
	if(is_built_in(start))
	{
		handle_built_ins(&start, mini);
		freethem(temp, mini);
		free_things(mini);
		exit(mini->return_code);
	}
	else
		mini->return_code = handle_cmd_pipe(&start, mini);
}

static void process_pipe_segment(t_token **temp, int *fd_in, 
	t_mini *mini, t_token **token)
{
    int 	pipefd[2];
    t_token *start;
	int		status;

	status = 0;
	while (temp && *temp)
	{
		mini->is_pipe = 2;
		start = *temp;
		if((*temp)->next)
			check_pipes(mini, temp);
		if (mini->is_pipe == 1)
			pipe(pipefd);
		g_pid = fork();
		if (g_pid== 0)
			setup_pipes(fd_in, pipefd, start, temp, mini);
		else
			handle_parent_process(pipefd, fd_in, mini, temp);
		if(mini->return_code == 127)
			handle_exit(token, mini);
	}
    waitpid(g_pid, &status, 0);
	if(WIFEXITED(status))
			mini->return_code = WEXITSTATUS(status);
}

void pipes(t_token **token, t_mini *mini)
{
    int fd_in;
    t_token *temp;

	temp = *token;
	fd_in = 0;
	if (!mini->final_pipe)
        	process_pipe_segment(&temp, &fd_in, mini, token);
	else
	{
		mini->return_code = 0;
		ft_printf(Error_Msg(ERROR_PIPE));
		mini->final_pipe = 0;
	}
}
