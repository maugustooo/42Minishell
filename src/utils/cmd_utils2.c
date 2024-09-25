/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:13:27 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/24 10:18:04 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file_perms(t_token *token)
{
	struct stat	path_stat;

	if(stat(token->text, &path_stat) == -1)
		return (0);
	if (S_ISREG(path_stat.st_mode))
	{
		if(access(token->text, R_OK | X_OK) == 0)
			return (1);
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_ISDIR), token->text);
		return (0);
	}
	return (0);
}