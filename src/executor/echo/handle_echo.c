/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:33:54 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/05 11:15:13 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Not Sus
void	handle_echo(char *flag, t_token *next, t_mini *mini)
{
	if (next && !mini->echo_flag)
		ft_printf("%s", next->text);
	else if (next->next)
		ft_printf("%s", next->next->text);
	else if(flag && next->next)
		ft_printf("%s", next->next->text);
	if(mini->echo_flag == false)
		ft_printf("\n");
	mini->echo_flag = false;
}
