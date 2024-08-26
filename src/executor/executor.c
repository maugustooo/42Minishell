/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:29:20 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/26 10:43:12 by maugusto         ###   ########.fr       */
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
	if (is_built_in(*token) && !mini->pipe)
        handle_built_ins(token, mini);
    else if(!mini->pipe)
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
	else
	{
	int pipefd[2];
    pid_t pid;
    int fd_in = 0; // Entrada do comando anterior
    t_token *temp = *token;
    t_token *start;
    int is_pipe;
    while (temp) 
	{
        start = temp;  // Início do comando atual

        // Percorre os tokens até o próximo pipe ou o final
        is_pipe = (temp->next && strcmp(temp->next->text, "|") == 0);
        while (temp->next && !is_pipe) {
            temp = temp->next;
            is_pipe = (temp->next && strcmp(temp->next->text, "|") == 0);
        }

        // Se houver um pipe, cria o pipe
        if (is_pipe) {
            pipe(pipefd);
        }

        pid = fork();
        if (pid == 0) {
            // No processo filho

            // Redireciona a entrada do processo filho para o pipe anterior
            if (fd_in != 0) {
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
            }

            // Redireciona a saída se houver um pipe para o próximo comando
            if (is_pipe) {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }

            // Fecha o lado de leitura do pipe no filho
            if (is_pipe) {
                close(pipefd[0]);
            }

            // Cria uma lista de argumentos para execve
            char *args[256];  // Buffer fixo para argumentos
            int i = 0;

            while (start != temp->next) {  // Até o próximo pipe ou o final
                args[i++] = start->text;
                start = start->next;
            }
            args[i] = NULL;  // Termina a lista de argumentos
            
            execvp(args[0], args);
            perror("execvp");  // Caso execvp falhe
            exit(EXIT_FAILURE);

        } else {
            // No processo pai

            // Espera o filho terminar
            waitpid(pid, NULL, 0);

            // Fecha o lado de escrita do pipe atual, se houver
            if (is_pipe) {
                close(pipefd[1]);
            }

            // Define a nova entrada para o próximo comando
            if (is_pipe) {
                fd_in = pipefd[0];
            }

            // Avança para o próximo comando, após o pipe
            if (is_pipe) {
                temp = temp->next->next;  // Pula o pipe para o próximo comando
            } else {
                temp = temp->next;  // Continua no próximo token
            }
        }
    }
}
}


/**@}*/