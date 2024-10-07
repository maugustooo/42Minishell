/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:58:22 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/07 10:52:04 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_export(t_mini *mini, t_token *token)
{
	int		i;
	int		j;
	char	**tenv;

	i = env_size(mini, NULL);
	tenv = ft_calloc((i + 2), sizeof(char *));
	if (!tenv)
		error_malloc(mini);
	j = 0;
	while (j < i)
	{
		tenv[j] = ft_strdup(mini->penv[j]);
		j++;
	}
	tenv[j] = ft_strdup(token->text);
	j++;
	tenv[j] = NULL;
	free_penv(mini);
	dup_tenv(mini, tenv);
}

void	check_arg_export(t_token *token, t_mini *mini)
{
	char	**key;
	int		i;

	key = NULL;
	i = -1;
	if (token->type == PIPE)
		return ;
	key = ft_split(token->text, '=');
	if (key && key[0] && ft_strlen(key[0]) > 0)
	{
		while (key[0][++i])
		{
			if (!ft_isalnum_under(key[0][i]))
				if (export_arg_err(token, mini, key))
					return ;
		}
	}
	if (!key[1])
		if (export_arg_err(token, mini, key))
			return ;
	free_key(key);
}

int	export_arg2(char **key, char *value)
{
	if (ft_strcmp(key[0], value) == 0)
		return (0);
	free_keys(&key);
	return (1);
}

void	export_arg2_5(t_token *token, t_mini *mini, int *i, char *value)
{
	free(mini->penv[*i]);
	expander(&token, mini);
	mini->penv[*i] = ft_strdup(token->text);
	free(value);
}

int	export_arg(t_token *token, t_mini *mini)
{
	char	*value;
	char	**key;
	char	**key2;
	int		i;

	i = -1;
	key2 = ft_split(token->text, '=');
	if (export_arg_err(token, mini, key2))
		return (0);
	value = get_env_key(mini, key2[0]);
	free_key(key2);
	if (value != NULL)
	{
		while (mini->penv[++i])
		{
			key = ft_split(mini->penv[i], '=');
			if (!export_arg2(key, value))
			{
				export_arg2_5(token, mini, &i, value);
				return (free_keys(&key), 0);
			}
		}
		free(value);
	}
	return (1);
}
