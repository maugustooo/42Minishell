/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:20:06 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/06 11:48:21 by maugusto         ###   ########.fr       */
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
	tmp_env = malloc((i + 1) * sizeof(char *));
	if (!tmp_env)
		return(NULL);
	while (j < i)
	{
		tmp_env[j] = ft_strdup(mini->penv[j]);
		j++;
	}
	tmp_env[j] = NULL;
	bsort(tmp_env, j);
	return (tmp_env);
}

void	free_env(char **tmp_env, char ***key)
{
	int		i;
	int		j;
	char	**casted_key;

	i = 0;
	j = -1;
	if (tmp_env)
	{
		while (tmp_env[i])
			i++;
		while (++j < i)
			free(tmp_env[j]);
		free(tmp_env);
	}
	i = 0;
	j = -1;
	if (key && *key)
	{
		casted_key = *key;
		while (casted_key[i])
			i++;
		while (++j < i)
			free(casted_key[j]);
		free(casted_key);
	}
}

void	export_no_args(t_mini *mini)
{
	char	**tmp_env;
	char	**key;
	int		i;


	tmp_env = handle_arr(mini);
	i = -1;
	key = NULL;
	while (tmp_env[++i])
	{
		key = ft_split(tmp_env[i], '=');
		if (ft_strcmp(key[0], "_") == 0)
		{
			free_env(NULL, &key);
			continue;
		}
		if(key[1] != NULL)
			ft_printf("declare -x %s=\"%s\"\n", key[0], key[1]);
		else
		{
			if(tmp_env[i][ft_strlen(tmp_env[i]) - 1] == '=')
				ft_printf("declare -x %s=\"\"\n", key[0]);
			else
				ft_printf("declare -x %s\n", key[0]);
		}
		free_keys(&key);
		key = NULL;
	}
	free_env(tmp_env, NULL);
}

void	handle_export(t_mini *mini, t_token *token)
{
	if(!mini->exported)
	{
		if (token)
		{
			while(token)
			{
				if(export_arg(token, mini))
					set_export(mini, token);
				token = token->next;
			}
			mini->return_code = 0;
		}
		else
		{
			export_no_args(mini);
			mini->return_code = 0;
		}
	}
}
