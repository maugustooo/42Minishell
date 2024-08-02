/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:20:06 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/02 14:12:44 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bsort(char **arr, int n)
{
	int		i;
	int 	j;
	char	*tmp;

	i = 0;
	j = 0;
	while(i < (n - 1))
	{
		j = 0;
		while(j < (n - i - 1))
		{
			if(ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**handle_arr(t_mini *mini)
{
	char		**tmp_env;
	int 		i;
	int 		j;

	i = 0;
	j = 0;
	while (mini->penv[i])
		i++;
	tmp_env = malloc(i * sizeof(char *));
	if (!tmp_env)
	{
		//TODO:Handle malloc error
	}
	while (j < i)
	{
		tmp_env[j] = mini->penv[j];
		j++;
	}
	tmp_env[j] = NULL;
	bsort(tmp_env, j);
	return (tmp_env);
}

void	handle_export(t_mini *mini)
{
	char	**tmp_env;
	char	**key;
	int		i;
	int		j;

	tmp_env = handle_arr(mini);
	i = 0;
	j = 0;
	while (tmp_env[i])
	{
		key = ft_split(tmp_env[i], '=');
		if (ft_strcmp(key[0], "_") == 0)
		{
			i++;
			continue;
		}
		if (tmp_env[i + 1] != NULL)
			ft_printf("declare -x %s=\"%s\"\n", key[0], key[1]);
		else
			ft_printf("declare -x %s=\"%s\"", key[0], key[1]);
		i++;
	}
	free(key);
	free(tmp_env);
}
