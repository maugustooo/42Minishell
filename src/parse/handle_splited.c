/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_splited.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:53:00 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/03 14:57:50 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_token(t_mini *mini, char *start, int len, int index)
{
	if (mini->splited[index])
		free(mini->splited[index]);
	// if(ft_find_c('<', mini->splited[index]))
	// {
	// 	ft_strtrim(e)
	// }
	mini->splited[index] = ft_strndup(start, len);
}

static void	handle_redirects(char **line, t_mini *mini, int *index, int *len, char **start)
{
	if (*len > 0)
	{
		add_token(mini, *start, *len, *index);
		(*index)++;
		*len = 0;
	}
	if((*(*line) == '>' && *(*line + 1) == '>')
		|| (*(*line) == '<' && *(*line + 1) == '<'))
	{
		add_token(mini, *line, 2, *index);
		(*line) = (*line) + 2;
		(*index)++;
	}
	else
	{
		add_token(mini, *line, 1, *index);
		(*line)++;
		(*index)++;
	}
}

static void handle_pipes(char **line, t_mini *mini, int *index, int *len, char **start)
{
	if (*len > 0)
	{
		add_token(mini, *start, *len, *index);
		(*index)++;
		*len = 0;
	}
	if (((mini->token_count - (*index) != 0) && mini->final_pipe)
		|| !mini->final_pipe)
	{
		add_token(mini, *line, 1, *index);
		(*index)++;
	}
	(*line)++;
}

static void	handle_spaces(char **line, int *len, t_mini *mini, int *index)
{
	if (*len > 0)
	{
		add_token(mini, *line - *len, *len, *index);
		(*index)++;
	}
	*len = 0;
	while (**line && ft_isspace(**line))
		(*line)++;
}

static void	process_tokens(char *line, t_mini *mini, int *index, int *in_quotes)
{
	char	*start;
	int		len;
	char	quote_char;

	len = 0;
	quote_char = '\0';
	while (*line)
	{
		handle_quotes(*line, in_quotes, &quote_char);
		if (!*in_quotes && ft_isspace(*line))
		{
			handle_spaces(&line, &len, mini, index);
			continue ;
		}
		if (!*in_quotes && ((*line == '|' || *line == '<' || *line == '>')
			|| (*line == '>' && *line + 1 =='>')))
		{
			if (*line == '|')
				handle_pipes(&line, mini, index, &len, &start);
			else
				handle_redirects(&line, mini, index, &len, &start);
			continue ;
		}
		if (len++ == 0)
			start = line;
		line++;
	}
	if (len > 0)
		add_token(mini, start, len, *index);
}

void	split_to_tokens(char *line, t_mini *mini)
{
    int index;
	int in_quotes;
	
	in_quotes = 0;
	index = 0;
    if (!line || !line[0])
        return;
    mini->token_count = count_tokens(line, mini);
	mini->splited = ft_calloc((mini->token_count + 1), sizeof(char *));
    if (!mini->splited)
        return ;
    process_tokens(line, mini, &index, &in_quotes);
	if(index == mini->token_count)
    	mini->splited[index] = NULL;
	else
		mini->splited[index + 1] = NULL;
}
