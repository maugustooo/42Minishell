/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:58:22 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/29 14:33:13 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_export(t_mini *mini, t_token *token)
{
	int		i;
	int		j;
	char	**tenv;

	i = env_size(mini, NULL);
	tenv = ft_calloc((i + 2), sizeof(char *));
	if(!tenv)
		return ;
	j = 0;
	while (j < i)
	{
		tenv[j] = ft_strdup(mini->penv[j]);
		j++;
	}
	tenv[j] = ft_strdup(token->text);
	j++;
	tenv[j] = NULL;
	free_penv(mini);
	dup_tenv(mini, tenv);
}
