/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:52:10 by maugusto          #+#    #+#             */
/*   Updated: 2024/09/23 12:22:26 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief will handle the ctrl+C to display a new line
 * 
 * @param sig SIGINT
 */
void	handle_sigint(int sig)
{
	(void) sig;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Will handle the ctrl+D to exit
 * 
*/
void	handle_eof(t_token **token, t_mini *mini)
{
	ft_printf("exit\n");
	handle_exit(token, mini);
}

void	ft_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
