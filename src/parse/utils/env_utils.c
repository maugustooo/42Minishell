/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:14:01 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/02 09:18:10 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Duplicate environment variables
 * 
 * @return char** Duplicated matrix of environment variables
*/
char	**dup_env()
{
	extern char **environ;
	char		**penv;
	int			count;
	int			i;
	
	count = 0;
	while(environ[count])
		count++;
	penv = malloc(sizeof(char *) * count);
	if(!penv)
		//TODO:HANDLE MALLOC ERROR
	i = 0;
	while (i < count)
	{
		penv[i] = environ[i];
		i++;
	}
	return (penv);
}
