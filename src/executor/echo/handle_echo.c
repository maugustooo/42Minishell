/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:33:54 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/12 16:01:05 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_input(t_token *token)
{
	int fd;
	char *file;

	token = token->next;
	file = token->next->text;
	fd = open(file, O_RDONLY);
	ft_printf_fd(fd, token->text);
}
//Not Sus
void	handle_echo(t_token *next, t_mini *mini)
{
	int first;

	first = 0;
	while (next)
	{
		if(next->next->type == INPUT)
			handle_input(next);
		if(next && first == 2)
		{
			ft_printf("%s", next->text);
			first = 2;
		}
		if (next && !mini->echo_flag)
			ft_printf("%s", next->text);
		else if (next->next && !first)
		{
			next = next->next;
			ft_printf("%s", next->text);
			first = 2;
		}
		next = next->next;
		if(next)
			ft_printf(" ");	
	}
	if(mini->echo_flag == false)
			ft_printf("\n");
	mini->echo_flag = false;
}
