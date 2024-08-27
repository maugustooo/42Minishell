/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:53:00 by maugusto          #+#    #+#             */
/*   Updated: 2024/08/27 11:11:23 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static void add_token(t_mini *mini, char *start, int len, int index)
{
    if (mini->splited[index])
    	free(mini->splited[index]);
    mini->splited[index] = ft_strndup(start, len);
}

static int count_tokens(char *line)
{
    int count = 0;
    int in_quotes = 0;
    char quote_char = '\0';

    while (*line)
    {
        if ((*line == '"' || *line == '\'') && !in_quotes)
        {
            in_quotes = 1;
            quote_char = *line;
        }
        else if (*line == quote_char && in_quotes)
            in_quotes = 0;
        else if (!in_quotes &&  (isspace(*line) || *line == '|'))
        {
            count++;
            while (*line && ft_isspace(*line))
                line++;
            continue;
        }
        line++;
    }
   if (*(line - 1) && !isspace(*(line - 1)) && *(line - 1) != '|')
        count++;
    return (count);
}

static void handle_quotes(char *c, int *in_quotes, char *quote_char)
{
    if ((*c == '"' || *c == '\'') && !*in_quotes)
    {
        *in_quotes = 1;
        *quote_char = *c;
    }
    else if (*c == *quote_char && *in_quotes)
        *in_quotes = 0;
}
static int handle_pipes(char *line, t_mini *mini, int *index, int *len, char **start)
{
    if (*len > 0)
    {
        add_token(mini, *start, *len, *index);
        (*index)++;
        *len = 0;
    }
    add_token(mini, line, 1, *index);
    (*index)++;
    return (1);
}

static void process_tokens(char *line, t_mini *mini, int *index, int *len, int *in_quotes, char *quote_char)
{
    char *start;

    while (*line)
    {
        handle_quotes(line, in_quotes, quote_char);
        if (!*in_quotes && ft_isspace(*line))
        {
            if (*len > 0)
            {
                add_token(mini, start, *len, *index);
                (*index)++;
            }
            *len = 0;
            while (*line && ft_isspace(*line))
                line++;
            continue;
        }
		if (!*in_quotes && *line == '|')
        {
            if (handle_pipes(line, mini, index, len, &start))
            {
                line++;
                continue;
            }
        }
        if (*len == 0)
            start = line;
        (*len)++;
        line++;
    }
    if (*len > 0)
        add_token(mini, start, *len, *index);
}

void split_to_tokens(char *line, t_mini *mini)
{
    int token_count;
    int len;
    int index;
    int in_quotes;
    char quote_char;

    len = 0;
    index = 0;
    in_quotes = 0;
    quote_char = '\0';
    if (!line || !line[0])
        return;
    token_count = count_tokens(line);
    if (mini->splited != NULL)
        free(mini->splited);
    mini->splited = ft_calloc((token_count + 1), sizeof(char *));
    if (!mini->splited)
        return;
    process_tokens(line, mini, &index, &len, &in_quotes, &quote_char);
    mini->splited[index + 1] = NULL;
}
