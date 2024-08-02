/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:38:13 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/02 11:07:57 by gude-jes         ###   ########.fr       */
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
	}
	else
	{
		// if(mini->penv) TODO: Check no env
		// {
			while(mini->penv[i])
				ft_printf("%s\n", mini->penv[i++]);
		//}	
	}
}

