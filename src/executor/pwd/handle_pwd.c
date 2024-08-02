/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:34:17 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/02 14:26:03 by gude-jes         ###   ########.fr       */
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