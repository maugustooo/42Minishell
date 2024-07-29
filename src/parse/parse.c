/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:35:32 by maugusto          #+#    #+#             */
/*   Updated: 2024/07/29 15:48:15 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * @brief Get the line in prompt
 * 
 * @param mini The struct of the minishell
 * @return void* 
 */
void *get_line(t_mini *mini)
{
	char *rl;
	rl = readline("MiniShell: ");
	mini->line = rl;
	ft_printf("%s", mini->line);
	get_tokens(mini);
}