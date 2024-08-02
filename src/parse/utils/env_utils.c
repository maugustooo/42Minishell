/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:14:01 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/02 10:49:51 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Duplicate environment variables
 * 
 * @param mini the struct
*/
void	dup_env(t_mini *mini)
{
	extern char **environ;
	int			count;
	int			i;
	
	i = 0;
	count = 0;
	while(environ[count])
		count++;
	mini->penv = malloc(sizeof(char *) * count);
	if(!mini->penv)
		//TODO:HANDLE MALLOC ERROR
	i = 0;
	while (i < count)
	{
		mini->penv[i] = environ[i];
		i++;
	}
}
