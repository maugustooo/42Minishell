/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:35:32 by maugusto          #+#    #+#             */
/*   Updated: 2024/07/31 15:22:37 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check(char	*cmd, t_token *token, t_mini *mini)
{
	t_token *current;

	current = token;
	if(ft_strncmp(cmd, "echo", 4) == 0)
		if(ft_strncmp(token->next->text, "-n", 2) == 0)
			mini->echo_flag = true;
	if(ft_strncmp(cmd, "cd", 2) == 0|| ft_strncmp(cmd, "echo", 4) == 0
		|| ft_strncmp(cmd, "pwd", 3) == 0|| ft_strncmp(cmd, "export", 6) == 0
		|| ft_strncmp(cmd, "unset", 5) == 0|| ft_strncmp(cmd, "exit", 4) == 0
		|| ft_strncmp(cmd, "exit", 4) == 0 || ft_strncmp(cmd, "env", 4) == 0)
			return(1);
	return(0);
}
/**
 * @brief Get the line in prompt
 * 
 * @param mini The struct of the minishell
 * @return void* 
 */
int parse(t_mini *mini, t_token	**token)
{
	char *rl;
	char **splited;
	
	splited = NULL;
	while(1)
	{
		rl = readline("\nMiniShell: ");
		mini->line = rl;
		splited = ft_split(mini->line, ' ');
		if(!*splited)
			continue;
		if(!check(*splited, *token, mini))
		{
			ft_printf(Error_Msg(ERROR_CMD), *splited);
			continue;
		}
		get_tokens(token, &splited);
		executor(token);
		ft_tokenclear(token);	
		free(splited);
	}
	return(1);
}
