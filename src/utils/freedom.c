/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:05:26 by maugusto          #+#    #+#             */
/*   Updated: 2024/11/03 18:35:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i ++;
	}
	free(args);
}

void	free_key(char **key)
{
	if (key)
	{
		free(key[0]);
		free(key[1]);
		free(key);
	}
}

void	free_things(t_mini *mini)
{
	if(mini->saved_stdout)
		close(mini->saved_stdout);
	if(mini->saved_stdin)
		close(mini->saved_stdin);
	if (mini->penv)
	{
		free_penv(mini);
		mini->penv = NULL;
	}
	if (mini->prev_dir)
	{
		free(mini->prev_dir);
		mini->prev_dir = NULL;
	}
}

void	free_in_main(t_token **token, t_mini *mini)
{
	free_things(mini);
	freethem(token, mini);
}

/**
 * @brief free the params
 * 
 * @param token the list of tokens
 * @param splited the tokens splited
 */
void	freethem(t_token **token, t_mini *mini)
{
	int	i;

	i = 0;
	mini->pipe = 0;
	if (token)
		ft_tokenclear(token);
	if (mini->splited)
	{
		while (mini->splited[i])
			free(mini->splited[i++]);
		free(mini->splited);
		mini->splited = NULL;
	}
	mini->exported = false;
}
