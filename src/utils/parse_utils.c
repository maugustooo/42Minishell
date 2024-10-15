/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:56:12 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/15 12:06:11 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_perms(t_token *temp, int input)
{
	if (temp->type == NO_PERM && (input || (ft_find_c('<', temp->text)
				|| ft_find_c('>', temp->text)
				|| (ft_find_c('<', temp->text)
					&& ft_find_c('<', temp->text + 1)))))
	{
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_PERMS), temp->text);
		return (0);
	}
	return (1);
}

int	return_redirect(t_token *token)
{
	return (token->type == INPUT || token->type == OUTPUT
		|| token->type == APPEND || token->type == DELIMITER);
}

int	get_redirects(t_token *token)
{
	return (token->type == INPUT || token->type == OUTPUT
		|| token->type == APPEND);
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
