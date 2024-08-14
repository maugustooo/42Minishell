/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:29:20 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/14 15:51:21 by maugusto         ###   ########.fr       */
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
    int pipefd[2];
    pid_t pid;
    int fd_in = 0; // Entrada do comando anterior
    t_token *temp = *token;
    t_token *start;

    while (temp)
    {
        start = temp;  // Início do comando atual

        // Percorre os tokens até o próximo pipe ou o final
        while (temp->next && strcmp(temp->next->text, "|") != 0)
            temp = temp->next;

        // Se pipe encontrado, cria o pipe
        if (temp->next && strcmp(temp->next->text, "|") == 0)
            pipe(pipefd);

        pid = fork();
        if (pid == 0)
        {
            // Redireciona a entrada do processo filho para o pipe anterior
            if (fd_in != 0)
            {
                dup2(fd_in, 0);
                close(fd_in);
            }

            // Redireciona a saída se houver um pipe para o próximo comando
            if (temp->next && strcmp(temp->next->text, "|") == 0)
            {
                dup2(pipefd[1], 1);
                close(pipefd[1]);
            }

            // Fecha o lado de leitura do pipe no filho
            if (pipefd[0] > 0)
            {
                close(pipefd[0]);
            }

            // Cria uma lista de argumentos para execve
            char *args[256];  // Buffer fixo para argumentos
            int i = 0;

            while (start != temp->next)  // Até o próximo pipe ou o final
            {
                args[i++] = start->text;
                start = start->next;
            }
            args[i] = NULL;  // Termina a lista de argumentos

            // Executa o comando
            if (is_built_in(*token))
            {
                handle_built_ins(token, mini);
            }
            else
            {
                execve(args[0], args, mini->penv);
                perror("execve"); // Apenas executa se não for built-in
            }
            exit(EXIT_FAILURE); // Se execve falhar ou built-in executar, sair
        }
        else
        {
            // No processo pai
            waitpid(pid, NULL, 0);  // Espera o filho terminar
            close(pipefd[1]);  // Fecha a escrita do pipe atual
            fd_in = pipefd[0];  // Guarda o final da leitura do pipe atual

            // Avança para o próximo comando, após o pipe
            if (temp->next && strcmp(temp->next->text, "|") == 0)
            {
                temp = temp->next->next;  // Pula o pipe para o próximo comando
            }
            else
            {
                temp = temp->next;  // Continua no próximo token
            }
        }
    }
}


/**@}*/