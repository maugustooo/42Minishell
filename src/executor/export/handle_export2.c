/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:58:22 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/20 11:44:53 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_export_expander(t_token *token, t_mini *mini)
{
	char	*tmp;
	char	**key;
	char	*expanded_value;

	tmp = ft_strdup(token->text);
	expander(&token, mini);
	if(ft_strcmp(token->text, "") == 0)
	{
		key = ft_split(tmp, '=');
		if(key[0])
		{
			expanded_value = ft_strjoin(key[0], "=");
			change_token_text(token, expanded_value);
		}
		free_key(key);
	}
	free(tmp);
}

void	set_export(t_mini *mini, t_token *token)
{
	int		i;
	int		j;
	char	**tenv;

	i = env_size(mini, NULL);
	tenv = ft_calloc((i + 2), sizeof(char *));
	if (!tenv)
		return ;
	j = 0;
	while (j < i)
	{
		tenv[j] = ft_strdup(mini->penv[j]);
		j++;
	}
	check_export_expander(token, mini);
	tenv[j] = ft_strdup(token->text);
	j++;
	tenv[j] = NULL;
	free_penv(mini);
	dup_tenv(mini, tenv);
}

static int	export_arg_err(t_token *token, t_mini *mini, char **key)
{
	if ((key[0] == NULL)
		|| (!ft_str_isalpha(key[0]) && !ft_strchr(key[0], '_')))
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_EXPORT), token->text);
		mini->return_code = 1;
		mini->exported = true;
		free_key(key);
		return (1);
	}
	return (0);
}

void	check_arg_export(t_token *token, t_mini *mini)
{
	char	*value;
	char	**key;
	int		i;

	key = NULL;
	value = NULL;
	i = -1;
	key = ft_split(token->text, '=');
	if (key[0])
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

int	export_arg(t_token *token, t_mini *mini)
{
	char	*value;
	char	**key;
	char	**key2;
	int		i;

	i = -1;
	key2 = ft_split(token->text, '=');
	value = get_env_key(mini, key2[0]);
	free_key(key2);
	if (value != NULL)
	{
		while (mini->penv[++i])
		{
			key = ft_split(mini->penv[i], '=');
			if (ft_strcmp(key[0], value) == 0)
			{
				free(mini->penv[i]);
				mini->penv[i] = ft_strdup(token->text);
				free(value);
				free_keys(&key);
				return (0);
			}
			free_keys(&key);
		}
		free(value);
	}
	return (1);
}
