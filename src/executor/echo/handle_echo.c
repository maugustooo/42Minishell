/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:33:54 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/31 12:28:25 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Sus
void	handle_echo(char *flag, t_token *next)
{
	int	nline;

	nline = 0;
	if (flag && ft_strncmp(flag, "-n", ft_strlen(flag)) == 0)
		nline = 1;
	ft_printf("%s", next->text);
	if (nline)
		ft_printf("\n");
}
