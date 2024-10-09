/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:36:43 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/09 10:46:02 by gude-jes         ###   ########.fr       */
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

	i = env_size(mini, NULL);
	j = 0;
	k = 0;
	tenv = ft_calloc((i + 1), sizeof(char *));
	if (!tenv)
		return ;
	while (j < i)
	{
		if (ft_strcmp(mini->penv[j], str) == 0)
		{
			j++;
			continue ;
		}
		tenv[k] = ft_strdup(mini->penv[j]);
		j++;
		k++;
	}
	tenv[k] = NULL;
	free_penv(mini);
	dup_tenv(mini, tenv);
}

void	handle_unset(t_token *token, t_mini *mini)
{
	int		i;
	char	**key;
	t_token	*current;

	mini->return_code = 0;
	current = token->next;
	while (current)
	{
		i = 0;
		while (mini->penv[i])
		{
			key = ft_split(mini->penv[i], '=');
			if (ft_strcmp(key[0], current->text) == 0)
			{
				dup_env_if(mini, mini->penv[i]);
				free_unset(&key);
				break ;
			}
			free_unset(&key);
			i++;
		}
		current = current->next;
	}
	mini->return_code = 0;
}
