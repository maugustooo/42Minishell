/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:56:12 by maugusto          #+#    #+#             */
/*   Updated: 2024/11/01 15:38:09 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_perms(t_token *temp, int input, t_mini *mini)
{
	if (temp->type == NO_PERM && (input || (temp->prev && return_redirect(temp->prev)
		&& !mini->echo)))
	{
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_PERMS), temp->text);
		return (0);
	}
	return (1);
}

int	return_redirect(t_token *token)
{
	return (token->type == INPUT || token->type == OUTPUT
		|| token->type == APPEND || token->type == HERE);
}

int	get_redirects(t_token *token)
{
	return (token->type == INPUT || token->type == OUTPUT
		|| token->type == APPEND || !ft_strcmp(token->text, "<")
		|| !ft_strcmp(token->text, ">") || !ft_strcmp(token->text, ">>"));
}

int	pipes_and_red(char line)
{
	return ((line == '|'
			|| line == '<' || line == '>')
		|| (line == '>' && line + 1 == '>')
		|| (line == '<' && line + 1 == '<'));
}

int	check_redirects(char line)
{
	return ((line == '|' || line == '<' || line == '>')
		|| (line == '>' && line + 1 == '>')
		|| (line == '<' && line + 1 == '<'));
}
