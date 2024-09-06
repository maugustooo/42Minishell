/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:58:22 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/06 09:45:16 by gude-jes         ###   ########.fr       */
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
	if(!tenv)
		return ;
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

static int	export_arg_err(t_token *token, t_mini *mini, char **key)
{
	if ((key[0] == NULL) || 
		(!ft_str_isalpha(key[0]) && !ft_strchr(key[0], '_')))
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_EXPORT), token->next->text);
		mini->return_code = 1;
		mini->exported = true;
		free_key(key);
		return(1);
	}
	return(0);
}

void	check_arg_export(t_token *token, t_mini *mini)
{
	char	*value;
	char	**key;

	key = NULL;
	value = NULL;
	while (token->next)
	{
		key = ft_split(token->next->text, '=');
		if (token->next)
			if(export_arg_err(token, mini, key))
				return ;
		free_key(key);
		token = token->next;
	}
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
	if(value != NULL)
	{
		while(mini->penv[++i])
		{
			key = ft_split(mini->penv[i], '=');
			if(ft_strcmp(key[0], value) == 0)
			{
				free(mini->penv[i]);
				mini->penv[i] = ft_strdup(token->text);
				free(value);
				free_keys(&key);
				return(0);
			}
			free_keys(&key);
		}
		free(value);
	}
	return(1);
}
