/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:33:54 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/31 08:19:27 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Sus
void	handle_echo(t_token *flag, t_token *text)
{
	int	nline;

	if (flag && ft_strncmp(flag, "-n", ft_strlen(flag)) == 0)
		nline = 1;
	ft_printf("%s", text);
	if (nline)
		ft_printf("\n");
}
