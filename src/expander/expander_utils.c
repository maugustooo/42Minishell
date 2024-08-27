/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:07:08 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/27 14:51:48 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_not_sq(t_token **token,t_mini *mini,  int *i)
{
	char	*before;
	char	*after;
	char	*join;

	before = ft_strndup((*token)->text, *i);
	after = ft_strdup((*token)->text + *i);
	join = ft_strjoin(before, after);
	expand_input(mini, &after);
	free(before);
	*i += ft_strlen(after) - 1;
	free(after);
	free(join);
}

void	change_quotes(t_token **token, t_mini *mini)
{
	char	*text;
	char	*trimmed;

	text = NULL;
	trimmed = NULL;
	text = (*token)->text;
	trimmed = ft_strndup(text + 1, ft_strlen(text) - 2);
	if(text[0] == '\'' && text[ft_strlen(text) - 1] == '\'')
		change_token_text(&(*token)->text, trimmed);
	else if (text[0] == '"' && text[ft_strlen(text) - 1] == '"')
	{
		change_token_text(&(*token)->text, trimmed);
		expand_input(mini, &trimmed);
	}
	free(trimmed);
}
