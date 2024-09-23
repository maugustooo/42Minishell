/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:07:08 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/23 09:43:14 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_part(char *result, char *text, int *i, char quote)
{
	char	*part;
	int		start;

	start = *i;
	part = NULL;
	if (quote)
	{
		(*i)++;
		while (text[*i] && text[*i] != quote)
			(*i)++;
		part = ft_strndup(text + start + 1, (*i) - start - 1);
		(*i)++;
	}
	else
	{
		while (text[*i] && text[*i] != '"' && text[*i] != '\'')
			(*i)++;
		part = ft_strndup(text + start, *i - start);
	}
	result = ft_strjoin_free(result, part, 3);
	return (result);
}

void	change_quotes(t_token **token)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while ((*token)->text[i])
	{
		if ((*token)->text[i] == '\'' || (*token)->text[i] == '"')
			result = append_part(result, (*token)->text, &i, (*token)->text[i]);
		else
			result = append_part(result, (*token)->text, &i, 0);
	}
	change_token_text(*token, result);
}

char	*handle_sign2(t_token **token, t_mini *mini, int *i, int *len)
{
	char	*tmp;
	char	*seg;
	char	*original_var;

	tmp = NULL;
	tmp = ft_strndup((*token)->text + *i, *len);
	original_var = get_env_value(mini, tmp);
	if (original_var && ft_strcmp(tmp, original_var) == 0)
	{
		*i += *len;
		free(tmp);
		return (ft_strdup(""));
	}
	*i += *len;
	seg = get_env_value(mini, tmp);
	free(tmp);
	return (seg);
}

char	*handle_dq2(t_token **token, t_mini *mini, int *i, int *start,
	char *segment)
{
	char	*expanded;
	char	*temp;

	if (*i > *start)
	{
		temp = ft_strndup((*token)->text + *start, *i - *start);
		if (!temp)
			return (NULL);
		segment = ft_strjoin_free(segment, temp, 3);
	}
	expanded = handle_sign(token, mini, i, start);
	if (!expanded)
		return (NULL);
	segment = ft_strjoin_free(segment, expanded, 3);
	*start = *i;
	return (segment);
}
