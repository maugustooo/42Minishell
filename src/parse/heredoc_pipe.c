/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:54:39 by marvin            #+#    #+#             */
/*   Updated: 2024/11/03 14:54:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	move_left_heredoc_token(t_token **token)
{
    while ((*token)->next && (*token)->type != HERE)
    {
        *token = (*token)->next;
    }
	if ((*token)->type == HERE)
	{
		remove_node(token);
		remove_node(token);
	}
    while ((*token)->prev)
        *token = (*token)->prev;
}

static void close_and_move_left_token(t_token **current_token, int pipefd[2])
{
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    move_left_heredoc_token(current_token);
}

static char *set_delimiter_token(t_token *token)
{
    while (token)
    {
        if (token->type == HERE && token->next)
            return (token->next->text);
        token = token->next;
    }
    return (NULL);
}

static char *last_delimiter_token(t_token *token)
{
    char *delimiter;
    
    delimiter = NULL;
    while (token)
    {
        if (token->type == HERE && token->next)
            delimiter = token->next->text;
        token = token->next;
    }
    return (delimiter);
}


void heredoc_pipe(t_token **current_token, t_mini *mini)
{
    char buffer[1024];
    int bytes_read;
    char *delimiter;
    int pipefd[2];

    mini->redirect = 1;
    pipe(pipefd);
    signal(SIGINT, handle_sigint_heredoc);
    while (mini->here_count > 0)
    {
        delimiter = set_delimiter_token(*current_token);
        ft_printf_fd(mini->saved_stdout, "> ");
        bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
        if (bytes_read <= 0)
            break;
        buffer[bytes_read] = '\0';
        if (condition_hereoc(buffer, delimiter))
        {
            mini->here_count--;
            move_left_heredoc_token(current_token);
        }
        else if (strcmp(delimiter, last_delimiter_token(*current_token)) == 0)
            ft_printf_fd(pipefd[1], buffer);
    }
    close_and_move_left_token(current_token, pipefd);
}
