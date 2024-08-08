/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:20:06 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/08 13:51:49 by gude-jes         ###   ########.fr       */
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
		return(NULL);
	while (j < i)
	{
		tmp_env[j] = mini->penv[j];
		j++;
	}
	tmp_env[j] = NULL;
	bsort(tmp_env, j);
	return (tmp_env);
}

void	export_print(char **key)
{
	if(key[1] != NULL)
		ft_printf("declare -x %s=\"%s\"\n", key[0], key[1]);
}

void	export_no_args(t_mini *mini)
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
		export_print(key);
		i++;
	}
	free(key);
	free(tmp_env);
}

void	handle_export(t_mini *mini, t_token *token)
{
	if(token)
		set_export(mini, token);
	else
		export_no_args(mini);
}