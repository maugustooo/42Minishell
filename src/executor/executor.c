/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:29:20 by gude-jes          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/26 15:37:59 by gude-jes         ###   ########.fr       */
=======
/*   Updated: 2024/08/26 14:22:12 by maugusto         ###   ########.fr       */
>>>>>>> b7058848e01da1f1fd527a3367203facc85c5445
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file executor.c
 * @brief Executor of minishell
 * 
*/

#include "minishell.h"

/**
 * @brief Checks if token is command
 * 
 * @param token Token
 * @return int 1 or 0
*/
int	is_built_in(t_token *token)
{
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
	if (ft_strncmp((*token)->text, "echo", 4) == 0 && (*token)->next)
		handle_echo((*token)->next, mini);
	else if (ft_strncmp((*token)->text, "echo", 4) == 0 && !(*token)->next)
		ft_printf("\n");
	else if (ft_strncmp((*token)->text, "cd", 2) == 0)
		handle_cd(*token, mini);
	else if (ft_strncmp((*token)->text, "env", 3) == 0)
		handle_env(mini, (*token)->next);
	else if (ft_strncmp((*token)->text, "pwd", 3) == 0)
		handle_pwd();
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
    char *args[256];
    int i = 0;
	int pipefd[2];
    int fd_in = 0;
    t_token *temp = *token;
    t_token *start;
    int is_pipe;
    pid_t pid = 0;
    int status;
    char *argv[] = {(*token)->text, NULL};
	if (is_built_in(*token) && !mini->pipe)
        handle_built_ins(token, mini);
    else if(!mini->pipe)
    {
		pid = fork();
        if (pid == 0) 
		{
            if (execvp((*token)->text, argv) == -1)
                perror("execvp");
            exit(EXIT_FAILURE);
        }
		else if (pid < 0)
            perror("fork");
        else
            waitpid(pid, &status, 0);
    }
	else
	{
		
		while (temp) 
		{
			start = temp;
			is_pipe = (temp->next && strcmp(temp->next->text, "|") == 0);
			while (temp->next && !is_pipe) 
			{
				temp = temp->next;
				is_pipe = (temp->next && strcmp(temp->next->text, "|") == 0);
			}
			if (is_pipe) 
				pipe(pipefd);
			pid = fork();
			if (pid == 0)
			{
				if (fd_in != 0)
				{
					dup2(fd_in, STDIN_FILENO);
					close(fd_in);
				}
				if (is_pipe)
				{
					dup2(pipefd[1], STDOUT_FILENO);
					close(pipefd[1]);
				}
				if (is_pipe) 
					close(pipefd[0]);
				while (start != temp->next)
				{
					args[i++] = start->text;
					start = start->next;
				}
				args[i] = NULL;
				execvp(args[0], args);
				perror("execvp");
				exit(EXIT_FAILURE);
			} 
			else 
			{
				waitpid(pid, NULL, 0);
				if (is_pipe)
					close(pipefd[1]);
				if (is_pipe)
					fd_in = pipefd[0];
				if (is_pipe)
					temp = temp->next->next;
				else
					temp = temp->next;
			}
		}
}
}


/**@}*/