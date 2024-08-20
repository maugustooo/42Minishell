/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:05:58 by maugusto          #+#    #+#             */
/*   Updated: 2024/08/20 17:00:15 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	detect_expansion(t_token *token)
{
	int		i;
	bool	contains_sign;
	bool	sq;
	bool	dq;

	i = 0;
	contains_sign = false;
	sq = false;
	dq = false;
	while(token->text[i])
	{
		if(token->text[i] == '\'' && !sq)
			sq = !sq;
		else if (token->text[i] == '"' && !dq)
			dq = !dq;
		else if (token->text[i] == '$' || token->text[i] == '\''
			|| token->text[i] =='\"' )
			contains_sign = true;
		i++;
	}
	if (sq || dq)
		return(0); //TODO: REPORTAR ERRO DE SINTAXE - SUBJECT
	if (contains_sign)
		return (1); // Tem expander
	return(0); //Nao tem expander
}

char *expander(char *input)
{
	char	*test;
	int		i;
	char	*var_name;
	char	*start;
	
	var_name =  NULL;
	i = -1;
	test = input;
	while (*test)
	{
		if(*test == '$')
			test++;
		start = test;
		while (*test && (ft_isalnum(*test) || *test == '_'))
			test++;
		var_name = ft_strndup(start, test - start);
		// ft_strncpy(var_name, start, test - start);
		ft_printf("%s\n", var_name);
		getenv(var_name);
	}
	return(NULL);
}