/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:38:13 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/31 12:35:40 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_env(t_token *next)
{
	extern char **environ;
	int i;

	i = 0;
	if(!next)
	{
		while(environ[i])
			ft_printf("%s\n", environ[i++]);
	}
	else
	{
		while(environ[i] != next->text && environ[i])
			i++;
		// if (environ[i] == '\0')
		// 	//TODO: NO ENV
		// else
		ft_printf("%s\n", environ[i]);
	}
}

