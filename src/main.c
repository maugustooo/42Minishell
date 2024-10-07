/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:38:40 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/07 13:41:48 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_pid;

/**
 * @brief on a loop, will handle the readlines, parse, do the executor and
 * free everything
 * 
 * @param mini the struct
 * @param token the list of tokens
 */
void	minishell(t_mini *mini, t_token	**token, char **envp)
{
	while (1)
	{
		ft_signals();
		mini->rl = readline("miniShell: ");
		if (!mini->rl)
			handle_eof(token, mini);
		mini->line = mini->rl;
		if (mini->line[0])
			split_to_tokens(mini->line, mini);
		if (!mini->splited || !mini->splited[0])
		{
			freethem(token, mini);
			continue ;
		}
		add_history(mini->line);
		if (!parse(mini, token, envp))
		{
			free_things(mini);
			freethem(token, mini);
			continue ;
		}
		executor(token, mini);
		freethem(token, mini);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	t_token	*token;

	(void)argc;
	(void)argv;
	token = NULL;
	ft_memset(&mini, 0, sizeof(t_mini));
	minishell(&mini, &token, envp);
}
