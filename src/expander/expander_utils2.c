/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:07:08 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/30 09:52:36 by gude-jes         ###   ########.fr       */
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
		start++;
		while(text[*i] && text[*i] != quote)
			(*i)++;
		part = ft_strndup(text + start, *i - start);
		(*i)++;
	}
	else
	{
		while (text[*i] && text[*i] != '"' && text[*i] != '\'')
			(*i)++;
		part = ft_strndup(text + start, *i - start);
	}
	result = ft_strjoin_free(result, part, 1);
	free(part);
	return(result);
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
	free(result);
}

char	*handle_sign2(t_token **token, t_mini *mini, int *i, int *len)
{
	char	*tmp;
	char	*seg;

	tmp = NULL;
	tmp = ft_strndup((*token)->text + *i, *len);
	*i += *len;
	seg = get_env_value(mini, tmp);
	free(tmp);
	return(seg);
}

bool	handle_dq2(char *expanded)
{
	free(expanded);
	return(true);
}