/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:07:08 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/28 12:26:31 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_not_sq(t_token **token,t_mini *mini,  int *i)
{
	char	*trimmed;

	trimmed = NULL;
	if(ft_strcmp((*token)->text, "$?") == 0)
	{
		free((*token)->text);
		(*token)->text = ft_itoa(mini->return_code);
	}
	else
	{
		trimmed = ft_strtrim((*token)->text, "\"");
		expand_input(*token, mini, &trimmed);
		*i += ft_strlen(trimmed) - 1;
		free(trimmed);
	}
}

void	change_quotes(t_token **token, t_mini *mini)
{
	char	*text;
	char	*trimmed;

	text = NULL;
	trimmed = NULL;
	text = (*token)->text;
	trimmed = ft_strndup(text, ft_strlen(text));
	if(text[0] == '\'' && text[ft_strlen(text) - 1] == '\'')
		change_token_text(*token, trimmed);
	else if (text[0] == '"' && text[ft_strlen(text) - 1] == '"')
	{
		change_token_text(*token, trimmed);
		expand_input(*token, mini, &trimmed);
	}
	free(trimmed);
}
