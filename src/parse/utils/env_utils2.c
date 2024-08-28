/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:19:25 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/28 17:01:24 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_keys(char ***key)
{
	int		i;
	char	**casted_key;

	i = 0;
	casted_key = *key;
	while (casted_key[i])
		free(casted_key[i++]);
	free(casted_key);
}

char	*get_env_key(t_mini *mini, char *str)
{
	int		i;
	char	**key;
	char	*rkey;

	i = 0;
	key = NULL;
	while (mini->penv[i])
	{
			key = ft_split(mini->penv[i], '=');
			if(ft_strcmp(key[0], str) == 0)
			{
				rkey = ft_strdup(key[0]);
				free_keys(&key);
				return(rkey);
			}
			free_keys(&key);
		i++;
	}
	return(NULL);
}

char	*get_env_value(t_mini *mini, char *str)
{
	int		i;
	char	**key;
	char	*vkey;

	i = 0;
	key = NULL;
	while (mini->penv[i])
	{
			key = ft_split(mini->penv[i], '=');
			if(ft_strcmp(key[0], str) == 0)
			{
				vkey = ft_strdup(key[1]);
				free_keys(&key);
				free(str);
				return(vkey);
			}
			free_keys(&key);
		i++;
	}
	return(NULL);
}