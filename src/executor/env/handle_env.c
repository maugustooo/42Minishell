/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:38:13 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/20 11:49:36 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env_path(t_mini *mini)
{
	char	*key;
	char	*value;

	key = get_env_key(mini, "PATH");
	if (!key)
	{
		free(key);
		return (0);
	}
	value = get_env_value(mini, "PATH");
	if (!value)
	{
		free(value);
		free(key);
		return (0);
	}
	free(value);
	free(key);
	return (1);
}

void	print_env(t_mini *mini)
{
	int		i;
	char	**key;

	i = -1;
	key = NULL;
	while(mini->penv[++i])
	{
		if(ft_find_c('=', mini->penv[i]))
			ft_printf("%s\n", mini->penv[i]);
	}
}

void	handle_env(t_mini *mini, t_token *token)
{
	int	i;

	i = 0;
	if (token->next && (ft_strcmp(token->next->text, "|") != 0))
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_SENV));
		mini->return_code = 1;
	}
	else
	{
		if (mini->penv && check_env_path(mini))
		{
			print_env(mini);
			mini->return_code = 0;
		}
		else
		{
			ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_CMD), token->text);
			mini->return_code = 1;
		}
	}
}
