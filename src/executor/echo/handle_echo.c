/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:33:54 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/01 17:01:13 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Sus
void	handle_echo(char *flag, t_token *next, t_mini *mini)
{
	if(mini->echo_flag == false)
		ft_printf("\n");
	if(!flag && next == NULL)
		ft_printf("\n");
	else if (!flag)
		ft_printf("%s\n", next->text);
	else
		ft_printf("%s", next->text);
}
