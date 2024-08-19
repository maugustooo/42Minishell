/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:58:22 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/19 10:54:19 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tpenv(t_mini *mini, char **tenv)
{
	int	i;
	int	j;

	i = 0;
	if(mini)
	{
		while(mini->penv[i])
			i++;
		j = -1;
		while(++j < i)
			free(mini->penv[i]);
		free(mini->penv);
	}
	if(tenv)
	{
		i = 0;
		while(tenv[i])
			i++;
		j = -1;
		while(++j < i)
			free(tenv[j]);
		free(tenv);
	}
}

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
		mini->penv[j] = NULL;
		j++;
	}
	tenv[j] = ft_strdup(token->text);
	free_tpenv(mini, NULL);
	dup_env(mini, tenv);
	free_tpenv(NULL, tenv);
}
