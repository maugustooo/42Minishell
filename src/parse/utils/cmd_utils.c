/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:05:42 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/13 09:42:30 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path(t_mini *mini)
{
	char	*checker;

	checker = get_env_key(mini, "PATH");
	if (checker == NULL)
		return (0);
	return (1);
}

int	check_access(char *full_path)
{
	struct stat path_stat;

	if (stat(full_path, &path_stat) == 0 && access(full_path, X_OK) == 0)
		return (1);
	return (0);
}
