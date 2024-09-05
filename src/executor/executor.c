#include "minishell.h"

static int handle_cmd(pid_t pid, t_token **token, t_mini *mini)
{
	t_token *temp;
    char **argv;
	int i;

	temp = *token;
	i = -1;
	argv = ft_calloc(mini->token_count + 1, sizeof(char *));
	pid = fork();
	if (pid == 0) 
	{
		change_token_text(*token, ft_strjoin(CMD_PATH, (*token)->text));
		while (temp)
		{
			argv[++i] = ft_strdup(temp->text);
			temp = temp->next;
		}
		argv[++i]= NULL;
		if (execve((*token)->text, argv, mini->penv) == -1)
			perror("execve");
		return(1);
	}
	return(0);
}
/**
 * @brief Checks if token is command
 * 
 * @param token Token
 * @return int 1 or 0
*/
int	is_built_in(t_token *token)
{
	if(!token)
		return(0);
    return(token->type == CMD
	&& (ft_strcmp(token->text, "cd") == 0
	|| ft_strcmp(token->text, "echo") == 0
	|| ft_strcmp(token->text, "env") == 0
	|| ft_strcmp(token->text, "pwd") == 0
	|| ft_strcmp(token->text, "export") == 0
	|| ft_strcmp(token->text, "unset") == 0
	|| ft_strcmp(token->text, "exit") == 0));
	
}

void	handle_built_ins(t_token **token, t_mini *mini)
{
	if (ft_strncmp((*token)->text, "echo", 4) == 0)
		handle_echo(token, mini);
	else if (ft_strncmp((*token)->text, "cd", 2) == 0)
		handle_cd(*token, mini);
	else if (ft_strncmp((*token)->text, "env", 3) == 0)
		handle_env(mini, (*token)->next);
	else if (ft_strncmp((*token)->text, "pwd", 3) == 0)
		handle_pwd(mini);
	else if ((ft_strncmp((*token)->text, "export", 6) == 0))
		handle_export(mini, (*token)->next);
	else if (ft_strncmp((*token)->text, "unset", 5) == 0)
	 	handle_unset(*token, mini);
	else if (ft_strncmp((*token)->text, "exit", 4) == 0)
		handle_exit(token, mini);
}

/**
 * @brief Handles the built in functions
 * 
 * @param token Command
 * @param next Arguments
*/
void executor(t_token **token, t_mini *mini)
{
    pid_t pid;
    int status;
	
	pid = 0;
	if (is_built_in(*token) && !mini->pipe)
	       handle_built_ins(token, mini);
	else if (!mini->pipe)
    {
		if (handle_cmd(pid, token, mini))
		{
			mini->return_code = 127;
			handle_exit(token, mini);
		}
		else if (pid < 0)
            perror("fork");
        else
            waitpid(pid, &status, 0);
    }
	else
		pipes(token, mini, pid);		
}
