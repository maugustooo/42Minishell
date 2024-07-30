/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:38:13 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/30 16:47:46 by gude-jes         ###   ########.fr       */
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
		while(environ[i] != next && environ[i] != '\0')
			i++;
		if (environ[i] == '\0')
			//TODO: NO ENV
		else
			ft_printf("%s\n", environ[i]);
	}
}

