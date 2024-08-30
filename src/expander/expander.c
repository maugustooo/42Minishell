/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:05:58 by maugusto          #+#    #+#             */
/*   Updated: 2024/08/30 08:30:48 by gude-jes         ###   ########.fr       */
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
	while((*token)->text[i])
	{
		if((*token)->text[i] == '\'' && !dq)
			sq = !sq;
		else if ((*token)->text[i] == '"' && !sq)
			dq = !dq;
		i++;
	}
	if (sq || dq)
		return(1);
	i = -1;
	while((*token)->text[++i])
	{
		if ((*token)->text[i] == '$')
			return(0);
	}
	return(2);
}

void	change_token_text(t_token *token, char *value)
{
	if(value)
	{
		free(token->text);
		token->text = ft_strdup(value);
	}
	else
	{
		free(token->text);
		token->text = ft_strdup("");
	}
}

void	expand_input(t_token *token, t_mini *mini, char **input)
{
	char *key;
	char *value;

	value = NULL;
	key = get_env_key(mini, *input + 1);
	if(!key)
		change_token_text(token, value);
	else
	{
		value = get_env_value(mini, *input + 1);
		if(!value)
			change_token_text(token, "");
		else
			change_token_text(token, value);
		free(value);
	}
	free(key);
}

void	expander(t_token **token, t_mini *mini)
{
	int		result;

	result = detect_expansion(token);
	if (result == 0)
		handle_expansion(token, mini);
	else if(result == 1)
	{
		ft_printf("%s", "Due to subject rules NO unclosed quotes");
		change_token_text(*token, NULL);
	}
	else
		change_quotes(token);
}
