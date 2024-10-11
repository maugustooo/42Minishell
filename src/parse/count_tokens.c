/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:49:49 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/11 15:50:26 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes_data(char c, t_splited_data *data)
{
	if ((c == '"' || c == '\'') && !data->in_quotes)
	{
		data->in_quotes = 1;
		data->quote_char = c;
	}
	else if (c == data->quote_char && data->in_quotes)
		data->in_quotes = 0;
}

void	handle_quotes(char c, int *in_quotes, char *quote_char)
{
	if ((c == '"' || c == '\'') && !in_quotes)
	{
		*in_quotes = 1;
		*quote_char = c;
	}
	else if (c == *quote_char && in_quotes)
		*in_quotes = 0;
}

int	pipes_and_red(char line)
{
	return ((line == '|'
			|| line == '<' || line == '>')
		|| (line == '>' && line + 1 == '>')
		|| (line == '<' && line + 1 == '<'));
}

static void	increment_token_count(char **line, int *count, int in_quotes)
{
	if (!in_quotes && (!ft_isspace(**line) && !pipes_and_red(**line)))
		return ;
	(*count)++;
	if (!in_quotes)
	{
		while (**line && (ft_isspace(**line) || pipes_and_red(**line)))
		{
			if ((!in_quotes && (pipes_and_red(**line))))
			{
				(*count)++;
				while ((**line && (pipes_and_red(**line))))
					(*line)++;
			}
			if (**line)
				(*line)++;
		}
	}
}

static void	check_final_pipe(char *line, t_mini *mini, int *count)
{
	int	i;
	int	last_flag;

	i = 1;
	last_flag = 0;
	while (!last_flag && *line)
	{
		if (*(line - i) == '|')
		{
			mini->final_pipe = true;
			(*count)--;
			last_flag = 1;
		}
		else if (!ft_isspace(*(line - i)) && *(line - i) != '\0'
			&& ft_isascii(*(line - i)))
			last_flag = 1;
		i++;
	}
}

int	count_tokens(char *line, t_mini *mini)
{
	int		count;
	int		in_quotes;
	char	quote_char;

	count = 0;
	in_quotes = 0;
	quote_char = '\0';
	while (*line)
	{
		handle_quotes(*line, &in_quotes, &quote_char);
		increment_token_count(&line, &count, in_quotes);
		if (*line)
			line++;
	}
	if (*(line - 1) && !ft_isspace(*(line - 1)) && *(line - 1) != '|'
		&& *(line - 1) != '<' && *(line - 1) != '>')
		count++;
	check_final_pipe(line, mini, &count);
	return (count);
}
