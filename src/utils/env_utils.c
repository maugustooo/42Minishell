/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:14:01 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/24 09:52:57 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tenv(char **tenv)
{
	int	i;
	int	j;

	i = env_size(NULL, tenv);
	j = -1;
	while (++j < i)
	{
		free(tenv[j]);
		tenv[j] = NULL;
	}
	free(tenv);
}

void	free_penv(t_mini *mini)
{
	int	i;
	int	j;

	i = env_size(mini, NULL);
	j = -1;
	while (++j < i)
	{
		free(mini->penv[j]);
		mini->penv[j] = NULL;
	}
	free(mini->penv);
}

int	env_size(t_mini *mini, char **tenv)
{
	int	i;

	i = 0;
	if (tenv)
	{
		while (tenv[i])
			i++;
		return (i);
	}
	while (mini->penv[i])
		i++;
	return (i);
}

void	dup_tenv(t_mini *mini, char **tenv)
{
	int			count;
	int			i;

	i = 0;
	count = env_size(mini, tenv);
	mini->penv = malloc(sizeof(char *) * (count + 1));
	if (!mini->penv)
		error_malloc(mini);
	while (i < count)
	{
		mini->penv[i] = ft_strdup(tenv[i]);
		i++;
	}
	mini->penv[count] = NULL;
	free_tenv(tenv);
}

void	dup_envp(t_mini *mini, char **envp)
{
	int			count;
	int			i;

	i = 0;
	count = 0;
	while (envp[count])
		count++;
	mini->penv = malloc(sizeof(char *) * (count + 1));
	if (!mini->penv)
		error_malloc(mini);
	while (i < count)
	{
		mini->penv[i] = ft_strdup(envp[i]);
		i++;
	}
	mini->penv[count] = NULL;
}
