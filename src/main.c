/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:20:52 by maugusto          #+#    #+#             */
/*   Updated: 2024/08/13 14:16:09 by maugusto         ###   ########.fr       */
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

	rl = NULL;
	while(1)
	{
		rl = readline("miniShell: ");
		if (!rl)
            handle_eof(token, mini);
		mini->line = rl;
		if(mini->line[0])
			mini->splited = ft_split(mini->line, ' '); //Se mandar o readline vazio ele crasha por causa deste split.
		if(!mini->splited)
			continue;
		if(!parse(mini, token, envp))	
		{
			free_things(mini);
			freethem(token, mini);
			continue;
		}
		add_history(mini->line);
		executor(token, mini);
		freethem(token, mini);
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
