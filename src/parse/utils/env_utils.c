/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:14:01 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/14 14:37:25 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
		i++;
	j = -1;
	while (++j < i)
		free(envp[j]);
	free(envp);
}

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
	while (envp[count])
		count++;
	mini->penv = malloc(sizeof(char *) * (count + 1));
	//if(!mini->penv)
		//TODO:HANDLE MALLOC ERROR
	while (i < count)
	{
		mini->penv[i] = ft_strdup(envp[i]);
		i++;
	}
	mini->penv[count] = NULL;
}
