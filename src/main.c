/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:20:52 by maugusto          #+#    #+#             */
/*   Updated: 2024/08/02 10:48:56 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/**
 * @brief on a loop, will handle the readlines, parse, do the executor and free everything
 * 
 * @param mini the struct
 * @param token the list of tokens
 */
static void minishell(t_mini *mini, t_token	**token)
{
	char *rl;
	char **splited;
	
	splited = NULL;
	rl = NULL;
	while(1)
	{
		rl = readline("\nMiniShell: ");
		if (!rl)
            handle_eof();
		mini->line = rl;
		splited = ft_split(mini->line, ' ');
		if(!*splited)
			continue;
		if(!parse(mini, token, &splited))
		{
			freethem(token, splited);
			continue;
		}
		executor(token, mini);
		freethem(token, splited);
	}
}
int main()
{
	t_mini mini;
	t_token *token;
	
	
	token = NULL;
	ft_memset(&mini, 0, sizeof(t_mini));
	signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
	minishell(&mini, &token);
}
