/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:11:42 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/17 11:49:08 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dir(char *tgt_dir)
{
	struct stat	path_stat;

	if (!tgt_dir)
	{
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_HOME), tgt_dir);
		return (0);
	}
	if (stat(tgt_dir, &path_stat) == -1)
	{
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_CD), tgt_dir);
		return (0);
	}
	if (!S_ISDIR(path_stat.st_mode))
	{
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_CD), tgt_dir);
		return (0);
	}
	if (access(tgt_dir, R_OK | X_OK) == -1)
	{
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_PERMS), tgt_dir);
		return (0);
	}
	return (1);
}
