/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:36:43 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/19 10:49:17 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_unset(char ***key)
{
	char	**casted_key;
	int		i;
	int		j;

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

void	dup_env_if(t_mini *mini, char *str)
{
	char	**tenv;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while(mini->penv[i])
		i++;
	tenv = ft_calloc((i + 1), sizeof(char *));
	//TODO:Handle malloc error
	while (j < i)
	{
		if (ft_strcmp(mini->penv[j], str) == 0)
		{
			j++;
			continue;
		}
		tenv[k] = ft_strdup(mini->penv[j]);
		j++;
		k++;
	}
	tenv[k] = NULL;
	dup_env(mini, tenv);
	j = 0;
	while(tenv[j])
		free(tenv[j++]);
	free(tenv);
}

void	handle_unset(t_token *token, t_mini *mini)
{
	int		i;
	char	**key;

	i = 0;
	while(mini->penv[i])
	{
		key = ft_split(mini->penv[i], '=');
		if (ft_strcmp(key[0],token->next->text) == 0)
		{
			dup_env_if(mini, mini->penv[i]);
			free_unset(&key);
			break;
		}
		free_unset(&key);
		i++;
	}
}