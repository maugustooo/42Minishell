/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:12:45 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/18 12:18:57 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_ss_dolla(t_token **token, t_mini *mini, char *segment, int *i)
{
	pid_t	pid;

	pid = fork();
	if (pid != 0)
	{
		segment = ft_itoa(pid);
		waitpid(pid, NULL, 0);
	}
	else
	{
		free(mini->result);
		free_child(token, mini, NULL);
		exit(0);
	}
	(*i)++;
	return (segment);
}

char	*handle_special_signs2(t_token **token, t_mini *mini, int *i)
{
	char	*segment;
	char	*value;

	value = NULL;
	segment = NULL;
	if ((*token)->text[*i] == '$')
		segment = handle_ss_dolla(token, mini, segment, i);
	else if ((*token)->text[*i - 1] == '~')
	{
		value = get_env_value(mini, "HOME");
		if (value)
			segment = value;
	}
	return (segment);
}

void	badjeras(t_token **token, t_mini *mini)
{
	if(((*token)->text[0] == '"') || ((*token)->text[0]) == '\'')
	{
		if(ft_count_char((*token)->text, '\'',
				ft_strlen((*token)->text) -1) % 2 == 0
					|| ft_count_char((*token)->text, '"',
				ft_strlen((*token)->text) -1) % 2 == 0)
		{
			expander(token, mini);
			while((*token)->next && (ft_find_c('"', (*token)->text) == 0
				|| ft_find_c('\'', (*token)->text) == 0))
			{
				if (ft_find_c('"', (*token)->text)
					|| ft_find_c('\'', (*token)->text))
					expander(&(*token)->next, mini);
				*token = (*token)->next;
			}
			if (ft_find_c('"', (*token)->text) || ft_find_c('\'', (*token)->text))
					expander(token, mini);
		}
		while ((*token)->prev)
			*token = (*token)->prev;
	}
}
