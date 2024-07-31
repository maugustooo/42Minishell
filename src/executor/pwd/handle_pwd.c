/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:34:17 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/31 12:19:49 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pwd()
{
	char cwd[1024];
	if(getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	// else
	// 	//TODO: Handle ERROR
}