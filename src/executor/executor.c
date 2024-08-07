/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:29:20 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/07 10:02:05 by gude-jes         ###   ########.fr       */
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
	static char *prev_dir = NULL;//Bro em vez de declarar aqui, metemos na struct e trabalha com a struct para lidar com a memoria, e melhor ne?
	
	if (ft_strncmp((*token)->text, "cd", 2) == 0)
		handle_cd(*token, &prev_dir);
	else if (ft_strncmp((*token)->text, "echo", 4) == 0 && (*token)->next)
		handle_echo((*token)->next->text, (*token)->next, mini);
	else if (ft_strncmp((*token)->text, "env", 3) == 0)
		handle_env(mini, (*token)->next);
	else if (ft_strncmp((*token)->text, "pwd", 3) == 0)
		handle_pwd();
	else if ((ft_strncmp((*token)->text, "export", 6) == 0))
		handle_export(mini);
	// else if (ft_strncmp((*token)->text, "unset", 5) == 0)
	// 	handle_unset();
	else if (ft_strncmp((*token)->text, "exit", 4) == 0)
		handle_exit(&prev_dir);
}

/**
 * @brief Handles the built in functions
 * 
 * @param token Command
 * @param next Arguments
*/
void    executor(t_token **token, t_mini *mini)
{
	
    if (is_built_in(*token))
    {
		handle_built_ins(token, mini);
    }
    else
    {
       pid_t pid = fork();
        if (pid == 0) {
			char *argv[] = {(*token)->text, NULL};
            if (execvp((*token)->text, argv) == -1) {
                perror("execvp");
            }
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork");
        } else {
            int status;
            waitpid(pid, &status, 0);
        } 
    }
}

/**@}*/