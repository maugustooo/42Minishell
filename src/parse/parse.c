/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:35:32 by maugusto          #+#    #+#             */
/*   Updated: 2024/07/31 12:21:37 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * @brief Get the line in prompt
 * 
 * @param mini The struct of the minishell
 * @return void* 
 */
void get_line(t_mini *mini, t_token	**token)
{
	char *rl;
	char **splited;

	splited = NULL;
	while(1)
	{
		rl = readline("\nMiniShell: ");
		mini->line = rl;
		splited = ft_split(mini->line, ' ');
		get_tokens(token, &splited);
		executor(token);
		ft_tokenclear(token);
		free(splited);
	}
}
