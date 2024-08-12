/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:58:22 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/12 14:32:21 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_export(t_mini *mini, t_token *token)
{
	int		i;
	int		j;
	char	**tenv;

	i = 0;
	while(mini->penv[i])
		i++;
	tenv = ft_calloc((i + 2), sizeof(char *));
	//TODO: Handle malloc error
	j = 0;
	while (j < i)
	{
		tenv[j] = ft_strdup(mini->penv[j]);
		free(mini->penv[j]);
		j++;
	}
	tenv[j] = ft_strdup(token->text);
	free(mini->penv);
	dup_env(mini, tenv);
}
