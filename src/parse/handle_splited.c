/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_splited.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:53:00 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/07 11:04:33 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_token(t_mini *mini, char *start, int len, t_splited_data *data)
{
	if (mini->splited[data->index])
		free(mini->splited[data->index]);
	mini->splited[data->index] = ft_strndup(start, len);
}

static void	handle_redirects(char **line, t_mini *mini, t_splited_data *data, char **start)
{
	if (data->len > 0)
	{
		add_token(mini, *start, data->len, data);
		data->index++;
		data->len = 0;
	}
	if ((*(*line) == '>' && *(*line + 1) == '>')
		|| (*(*line) == '<' && *(*line + 1) == '<'))
	{
		add_token(mini, *line, 2, data);
		(*line) = (*line) + 2;
		data->index++;
	}
	else
	{
		add_token(mini, *line, 1, data);
		(*line)++;
		data->index++;
	}
}

static void handle_pipes(char **line, t_mini *mini, t_splited_data *data, char **start)
{
	if (data->len > 0)
	{
		add_token(mini, *start, data->len, data);
		data->index++;
		data->len = 0;
	}
	if (((mini->token_count - data->index != 0) && mini->final_pipe)
		|| !mini->final_pipe)
	{
		add_token(mini, *line, 1, data);
		data->index++;
	}
	(*line)++;
}

static void	handle_spaces(char **line, t_mini *mini, t_splited_data *data)
{
	if (data->len > 0)
	{
		add_token(mini, *line - data->len, data->len, data);
		data->index++;
	}
	data->len = 0;
	while (**line && ft_isspace(**line))
		(*line)++;
}

static void	process_tokens(char *line, t_mini *mini, t_splited_data *data)
{
	char	*start;
	char	quote_char;

	quote_char = '\0';
	while (*line)
	{
		handle_quotes(*line, data, &quote_char);
		if (!data->in_quotes && ft_isspace(*line))
		{
			handle_spaces(&line, mini, data);
			continue ;
		}
		if (!data->in_quotes && ((*line == '|' || *line == '<' || *line == '>')
				|| (*line == '>' && *line + 1 == '>')))
		{
			if (*line == '|')
				handle_pipes(&line, mini, data, &start);
			else
				handle_redirects(&line, mini, data, &start);
			continue ;
		}
		if (data->len++ == 0)
			start = line;
		line++;
	}
	if (data->len > 0)
		add_token(mini, start, data->len, data);
}

void	split_to_tokens(char *line, t_mini *mini)
{
	t_splited_data	data;

	ft_memset(&data, 0, sizeof(t_splited_data));
	if (!line || !line[0])
		return ;
	mini->token_count = count_tokens(line, mini, &data);
	mini->splited = ft_calloc((mini->token_count + 1), sizeof(char *));
	if (!mini->splited)
		return ;
	process_tokens(line, mini, &data);
	if (data.index == mini->token_count)
		mini->splited[data.index] = NULL;
	else
		mini->splited[data.index + 1] = NULL;
}
