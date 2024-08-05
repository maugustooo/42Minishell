/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:14:01 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/05 12:30:47 by maugusto         ###   ########.fr       */
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
	
	i = -1;
	count = 0;
	while (envp[count])
		count++;
	mini->penv = malloc(sizeof(char *) * (count + 1));
	if(!mini->penv)
		//TODO:HANDLE MALLOC ERROR
	while (++i < count)
		mini->penv[i] = ft_strdup(envp[i]);
	mini->penv[count] = NULL;
}
