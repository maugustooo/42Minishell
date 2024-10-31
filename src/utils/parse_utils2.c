/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:20:31 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/31 22:22:15 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_red(t_token *tmp)
{
	return (((!ft_find_c('>', tmp->text) || !ft_find_c('<', tmp->text))
				|| (!ft_find_c('>', tmp->text) && ft_find_c('>', tmp->text + 1)))
			&& !tmp->next);
}
void create_outfiles(t_token *tokens)
{
	int fd;
    t_token *current;
	
	current = tokens;
	fd = 0;
    while (current && current->type != NFILE)
	{
        if ((current->type == OUTPUT || current->type == APPEND) && current->next)
		{
			if(current->type == OUTPUT)
            	fd = open(current->next->text, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				fd = open(current->next->text, O_CREAT | O_WRONLY | O_APPEND, 0644);
            if (fd == -1)
				return ;
			else
				close(fd);
        }
        current = current->next;
    }
}

int	return_dup_files(t_token **token)
{
	return (((*token)->next->type == FILE
			|| (*token)->next->type == NFILE
			|| ((*token)->next->type == INPUT)
			|| ((*token)->type == INPUT)
			|| ((*token)->type == HERE)
			|| (*token)->prev->type == HERE) && ((*token)->next
			&& ((*token)->next->type != PIPE)));
}

int	next(t_token *tmp)
{
	return ((!ft_strcmp(tmp->text, "<<") && !tmp->next)
		|| ((!ft_strcmp(tmp->text, ">")
				|| !ft_strcmp(tmp->text, ">>") || !ft_strcmp(tmp->text, "<"))
			&& !tmp->next));
}

char	*set_delimiter(char **args, int *i, t_mini *mini)
{
	char	**tmp;
	int		j;
	char	*delimiter;

	delimiter = NULL;
	j = 0;
	tmp = args;
	if (mini->pipe)
	{
		while (tmp[j])
		{
			if (ft_strcmp(tmp[j], "<<") == 0)
			{
				if (tmp[j + 1])
					delimiter = tmp[j + 1];
				break ;
			}
			j++;
		}
	}
	else
		delimiter = args[*i + 1];
	return (delimiter);
}
