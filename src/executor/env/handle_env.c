/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:38:13 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/06 08:53:01 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_env(t_mini *mini, t_token *token)
{
	int i;

	i = 0;
	if(token->next && (ft_strcmp(token->next->text, "|") != 0))
		ft_printf("env: Options/Arguments not allowed by subject\n");
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

