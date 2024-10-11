/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:52:10 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/11 10:40:11 by gude-jes         ###   ########.fr       */
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
	if(sig == SIGINT)
	{
		g_sig = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_redisplay();
		signal(SIGINT, handle_sigint);
	}
}

void	handle_sigint2(int sig)
{
	if(sig == SIGINT)
	{
		g_sig = 130;
		write(STDOUT_FILENO, "\n", 1);
		signal(SIGINT, handle_sigint2);
	}
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
