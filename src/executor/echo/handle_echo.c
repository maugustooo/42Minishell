/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:33:54 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/08 14:31:34 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Not Sus
void	handle_echo(t_token *next, t_mini *mini)
{
	int first;

	first = 0;
	while (next)
	{
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
