/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:20:06 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/02 09:18:50 by gude-jes         ###   ########.fr       */
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

void	handle_export()
{
	extern char **environ;
	char		**tmp_env;
	int 		i;
	int 		j;

	i = 0;
	j = 0;
	while(environ[i])
		i++;
	tmp_env = malloc(i * sizeof(char *));
	if(!tmp_env)
	{
		//TODO:Handle malloc error
	}
	while(j < i)
	{
		tmp_env[j] = environ[j];
		j++;
	}
	bsort(tmp_env, j);
	j = 0;
	while(j < i)
	{
		ft_printf("declare -x %s\n", tmp_env[j]);
		j++;
	}
}
