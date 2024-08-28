/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:05:58 by maugusto          #+#    #+#             */
/*   Updated: 2024/08/28 14:41:01 by gude-jes         ###   ########.fr       */
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

// char *expander(char *input)
// {
// 	char	*test;
// 	int		i;
// 	char	*var_name;
// 	char	*start;
	
// 	var_name =  NULL;
// 	i = -1;
// 	test = input;
// 	while (*test)
// 	{
// 		if(*test == '$')
// 			test++;
// 		start = test;
// 		while (*test && (ft_isalnum(*test) || *test == '_'))
// 			test++;
// 		var_name = ft_strndup(start, test - start);
// 		// ft_strncpy(var_name, start, test - start);
// 		ft_printf("%s\n", var_name);
// 		getenv(var_name);
// 	}
// 	return(NULL);
// }

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

// void	handle_expansion(t_token **token, t_mini *mini)
// {
// 	int	i;
// 	int sq;
// 	int dq;

// 	i = 0;
// 	sq = 0;
// 	dq = 0;
// 	while ((*token)->text[i])
// 	{
// 		if ((*token)->text[i] == '"' && !sq)
// 			dq = !dq;
// 		else if ((*token)->text[i] == '\'' && !dq)
// 			sq = !sq;
// 		else if ((*token)->text[i] == '$' && !sq)
// 			handle_not_sq(token, mini, &i);
// 		i++;
// 	}
// }

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
		change_quotes(token, mini);
}
