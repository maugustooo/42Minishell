/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:10:25 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/02 10:39:14 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_sign(t_token **token, t_mini *mini, int *i, int *start)
{
	char	*segment;
	int		len;

	len = 1;
	(*i)++;
	if ((*token)->text[*i] == '?')
	{
		segment = ft_itoa(mini->return_code);
		(*i)++;
	}
	else if (ft_isalnum_under((*token)->text[*i]))
	{
		while (ft_isalnum_under((*token)->text[*i + len]))
			len++;
		segment = handle_sign2(token, mini, i, &len);
	}
	else if (!ft_isalnum_under((*token)->text[*i]) && (*token)->text[*i])
		segment = ft_strdup("");
	else
	{
		(*i)--;
		segment = ft_strdup("$");
		(*start)++;
	}
	return (segment);
}

char	*handle_sq(t_token **token, int *i)
{
	int		start;
	char	*segment;

	start = ++(*i);
	while ((*token)->text[*i] && (*token)->text[*i] != '\'')
		(*i)++;
	segment = ft_strndup(((*token)->text + start), *i - start);
	(*i)++;
	return (segment);
}

char	*handle_dq(t_token **token, t_mini *mini, int *i)
{
	char	*segment;
	int		start;

	segment = ft_strdup("");
	start = ++(*i);
	while ((*token)->text[*i] && (*token)->text[*i] != '"')
	{
		if ((*token)->text[*i] == '$'
			&& (ft_isalnum_under((*token)->text[*i + 1])
				|| ((*token)->text[*i + 1] == '?')))
			segment = handle_dq2(token, mini, i, &start, segment);
		else
			(*i)++;
	}
	if (*i > start)
		segment = ft_strjoin_free(segment,
				ft_strndup((*token)->text + start, *i - start), 3);
	(*i)++;
	return (segment);
}

char	*handle_plain(t_token **token, int *i)
{
	char	*segment;
	int		start;

	start = *i;
	while ((*token)->text[*i] && (*token)->text[*i] != '\''
		&& (*token)->text[*i] != '"' && (*token)->text[*i] != '$')
		(*i)++;
	segment = ft_strndup((*token)->text + start, *i - start);
	return (segment);
}

void	handle_expansion(t_token **token, t_mini *mini)
{
	char	*result;
	char	*expanded;
	int		i;
	char	*temp;

	i = 0;
	result = ft_strdup("");
	while ((*token)->text[i])
	{
		if ((*token)->text[i] == '\'')
			expanded = handle_sq(token, &i);
		else if ((*token)->text[i] == '"')
			expanded = handle_dq(token, mini, &i);
		else if ((*token)->text[i] == '$')
			expanded = handle_sign(token, mini, &i, &i);
		else
			expanded = handle_plain(token, &i);
		temp = ft_strjoin_free(result, expanded, 2);
		free(result);
		result = temp;
	}
	change_token_text(*token, result);
}
