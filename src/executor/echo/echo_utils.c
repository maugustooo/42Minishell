/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:11:25 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/30 10:13:41 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void heredoc(t_token *token, t_token *last)
{
    char *line;
    int fd;
    char *delimiter;

    delimiter = token->next->text;
    fd = open(last->text, O_WRONLY | O_CREAT | O_TRUNC, 0644);    
    if (fd < 0)
        return ;
    while (1)
    {
        line = readline("> ");
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        ft_putendl_fd(line, fd);
        free(line);
    }
    close(fd);
}

int	check_input(t_token *token, t_mini *mini)
{
	t_token *temp;
	t_token *last;

	temp = token;
	last = ft_tokenlast(token);
	while (temp && temp->type != PIPE)
	{
		if ((temp->type == OUTPUT || temp->type == APPEND) && !ft_find_c('"', temp->text) && !ft_find_c('\'', temp->text))
		{
			mini->echo_flag = true;
			if(!output(token, mini, last, temp->type))
				return(2);
			return (1);
		}
		if (temp->type == DELIMITER && !ft_find_c('"', temp->text) && !ft_find_c('\'', temp->text))
			heredoc(token, last);
		temp = temp->next;
	}
	return (0);
}
