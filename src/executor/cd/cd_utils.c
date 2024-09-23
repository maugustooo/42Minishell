/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:11:42 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/23 09:20:18 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dir(char *tgt_dir)
{
	struct stat	path_stat;

	if (stat(tgt_dir, &path_stat) == -1)
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_CD), tgt_dir);
		return (0);
	}
	if(!S_ISDIR(path_stat.st_mode))
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_NDIR), tgt_dir);
		return (0);
	}
	if(access(tgt_dir, R_OK | X_OK) == -1)
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_PERMS), tgt_dir);
		return (0);
	}
	return (1);
}
