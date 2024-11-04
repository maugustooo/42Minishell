/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:07:20 by gude-jes          #+#    #+#             */
/*   Updated: 2024/11/04 09:07:20 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_permission_error(char ***args, int *i, enum e_error error)
{
	ft_printf_fd(STDERR_FILENO, error_msg(error), (*args)[*i + 1]);
	move_left((*args), *i);
	move_left((*args), *i);
}

char	*remove_quotes(char *str)
{
	int		len;
	char	*new_str;

	len = ft_strlen(str);
	if ((str[0] == '"' && str[len - 1] == '"') || (str[0] == '\''
			&& str[len - 1] == '\''))
	{
		new_str = malloc(len - 1);
		if (!new_str)
			return (NULL);
		ft_strncpy(new_str, str + 1, len - 2);
		new_str[len - 2] = '\0';
		return (new_str);
	}
	return (str);
}
