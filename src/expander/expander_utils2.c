/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:07:08 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/28 17:01:31 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}

