/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:20:52 by maugusto          #+#    #+#             */
/*   Updated: 2024/08/02 15:55:19 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/**
 * @brief on a loop, will handle the readlines, parse, do the executor and free everything
 * 
 * @param mini the struct
 * @param token the list of tokens
 */
static void minishell(t_mini *mini, t_token	**token, char **envp)
{
	char *rl;
	char **splited;
	
	splited = NULL;
	rl = NULL;
	while(1)
	{
		rl = readline("MiniShell: ");
		if (!rl)
            handle_eof();
		mini->line = rl;
		splited = ft_split(mini->line, ' ');
		if(!*splited)
			continue;
		if(!parse(mini, token, &splited, envp))
		{
			freethem(token, splited);
			continue;
		}
		add_history(mini->line);
		executor(token, mini);
		freethem(token, splited);
	}
}
int main(int argc, char **argv, char **envp)
{
	t_mini mini;
	t_token *token;
	(void)argc;
	(void)argv;
	
	token = NULL;
	ft_memset(&mini, 0, sizeof(t_mini));
	signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
	minishell(&mini, &token, envp);
}
