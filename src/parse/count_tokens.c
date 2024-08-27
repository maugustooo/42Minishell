#include"minishell.h"

void handle_quotes(char c, int *in_quotes, char *quote_char)
{
    if ((c == '"' || c == '\'') && !(*in_quotes))
    {
        *in_quotes = 1;
        *quote_char = c;
    }
    else if (c == *quote_char && *in_quotes)
        *in_quotes = 0;
}

static void increment_token_count(char **line, int *count)
{
    if (!ft_isspace(**line) && **line != '|')
        return;
    (*count)++;
    while (**line && (ft_isspace(**line) || **line == '|'))
    {
        if (**line == '|')
        {
            (*count)++;
            while (**line && **line == '|')
                (*line)++;
        }
        if (**line)
            (*line)++;
    }
}

static void check_final_pipe(char *line, t_mini *mini, int *count)
{
    int i;
    int last_flag;

    i = 1;
    last_flag = 0;
    while (!last_flag)
    {
        if (*(line - i) == '|')
        {
            mini->final_pipe = true;
            (*count)--;
            last_flag = 1;
        }
        else if (!ft_isspace(*(line - i)) && *(line - i) != '\0' && ft_isascii(*(line - i)))
            last_flag = 1;
        i++;
    }
}

int count_tokens(char *line, t_mini *mini)
{
    int count;
    int in_quotes;
    char quote_char;

    count = 0;
    in_quotes = 0;
    quote_char = '\0';
    while (*line)
    {
        handle_quotes(*line, &in_quotes, &quote_char);
        if (!in_quotes)
            increment_token_count(&line, &count);
        if (*line)
            line++;
    }
    if (*(line - 1) && !ft_isspace(*(line - 1)) && *(line - 1) != '|')
        count++;
    check_final_pipe(line, mini, &count);
    return (count);
}
