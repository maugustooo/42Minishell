/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:38:13 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/26 14:59:04 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_env(t_mini *mini, t_token *next)
{
	int i;

	i = 0;
	if (next)
	{
		ft_printf("env: Options/Arguments not allowed by subject");
		mini->return_code = 1;
	}
	else
	{
		// if(mini->penv) TODO: Check no env
		// {
			while(mini->penv[i])
				ft_printf("%s\n", mini->penv[i++]);
		//}
		mini->return_code = 0;
	}
}

