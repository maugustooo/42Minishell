/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:58:07 by gude-jes          #+#    #+#             */
/*   Updated: 2024/11/01 15:58:22 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_n_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] && str[i] == 'n')
			i++;
		return (str[i] == '\0');
	}
	return (0);
}

int	handle_n_flag(t_token **next)
{
	int	n_flag;

	n_flag = 0;
	while ((*next) && (ft_strncmp((*next)->text, "-n", 2) == 0)
		&& check_valid_n_flag((*next)->text))
	{
		n_flag++;
		(*next) = (*next)->next;
	}
	return (n_flag);
}
