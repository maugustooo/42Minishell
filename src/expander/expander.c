/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:05:58 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/16 11:39:00 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	detect_expansion(t_token **token)
{
	int		i;
	bool	sq;
	bool	dq;

	i = 0;
	sq = false;
	dq = false;
	while ((*token)->text[i])
	{
		if ((*token)->text[i] == '\'' && !dq)
			sq = !sq;
		else if ((*token)->text[i] == '"' && !sq)
			dq = !dq;
		i++;
	}
	if (sq || dq)
		return (1);
	i = -1;
	while ((*token)->text[++i])
	{
		if ((*token)->text[i] == '$' || (*token)->text[i] == '~')
			return (0);
	}
	return (2);
}

void	change_token_text(t_token *token, char *value)
{
	if (value)
	{
		free(token->text);
		token->text = ft_strdup(value);
		free(value);
		value = NULL;
	}
	else
	{
		free(token->text);
		token->text = ft_strdup("");
	}
}

void	expander(t_token **token, t_mini *mini)
{
	int		result;

	result = detect_expansion(token);
	if (result == 0)
		handle_expansion(token, mini);
	else if (result == 1)
	{
		ft_printf("%s", "Due to subject rules NO unclosed quotes\n");
		mini->return_code = 2;
		change_token_text(*token, NULL);
	}
	else
		change_quotes(token);
}
