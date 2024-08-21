/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:05:58 by maugusto          #+#    #+#             */
/*   Updated: 2024/08/21 16:34:03 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	detect_expansion(t_token **token)
{
	int		i;
	bool	contains_sign;
	bool	sq;
	bool	dq;

	i = 0;
	contains_sign = false;
	sq = false;
	dq = false;
	while((*token)->text[i])
	{
		if((*token)->text[i] == '\'' && !sq && !dq)
			sq = !sq;
		else if ((*token)->text[i] == '"' && !dq && !sq)
			dq = !dq;
		else if ((*token)->text[i] == '$' && !sq)
			contains_sign = true;
		i++;
	}
	if (sq || dq)
		return(1);
	if (contains_sign)
		return (0);
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

void	expand_input(t_mini *mini, char **input)
{
	char *key;
	char *value;

	value = NULL;
	key = get_env_key(mini, *input + 1);
	if(!key)
		ft_printf("\n");
	else
	{
		value = get_env_value(mini, *input + 1);
		if(!value)
			ft_printf("\n");
		else
		{
			free(*input);
			*input = ft_strdup(value);
		}
		free(value);
	}
	free(key);
}

void	handle_expansion(t_token *token, t_mini *mini)
{
	int	i;
	int sq;
	int dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (token->text[i])
	{
		if (token->text[i] == '"' && !sq)
			dq = !dq;
		else if (token->text[i] == '\'' && !dq)
			sq = !sq;
		else if (token->text[i] == '$' && !sq)
		{
			i++;
			expand_input(mini, &token->text);
			i += (ft_strlen(token->text) - 1);
			continue;
		}
		i++;
	}
}

void	expander(t_token **token, t_mini *mini)
{
	int	result;

	result = detect_expansion(token);
	if (result == 0)
	{
		handle_expansion(*token, mini);
	}
	else if(result == 1)
		ft_printf("%s\n", "Due to subject rules NO unclosed quotes");
}
