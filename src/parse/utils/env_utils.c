/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:14:01 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/02 11:32:16 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Duplicate environment variables
 * 
 * @param mini the struct
*/
void	dup_env(t_mini *mini, char **envp)
{
	int			count;
	int			i;
	
	i = 0;
	count = 0;
	while(envp[count])
		count++;
	mini->penv = malloc(sizeof(char *) * count);
	if(!mini->penv)
		//TODO:HANDLE MALLOC ERROR
	i = 0;
	while (i < count)
	{
		mini->penv[i] = envp[i];
		i++;
	}
}
