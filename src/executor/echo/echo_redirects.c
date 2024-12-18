/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:07:50 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/15 14:17:07 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect2(t_token **next, int *len)
{
	if ((*next)->type == INPUT && ((*next)->text[0] != '"'
			&& (*next)->text[*len -1] != '"')
		&& ((*next)->text[0] != '\'' && (*next)->text[*len -1] != '\''))
	{
		(*next) = (*next)->next;
		return (1);
	}
	if (((*next)->text[1] == '"' && (*next)->text[*len -1] == '"')
		|| ((*next)->text[1] == '\'' && (*next)->text[*len -1] == '\''))
	{
		(*next) = (*next)->next;
		return (1);
	}
	return (0);
}

int	check_redirect(t_token **next)
{
	int	len;

	len = 0;
	if ((*next)->type == INPUT || (*next)->type == FILE
		|| (*next)->type == NFILE)
	{
		if ((*next)->type == FILE || (*next)->type == NFILE)
		{
			if ((*next)->type == NFILE)
				return (2);
			(*next) = (*next)->next;
			return (1);
		}
		len = ft_strlen((*next)->text);
		return (check_redirect2(next, &len));
	}
	return (0);
}
