/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:12:45 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/16 09:16:48 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_special_signs2(t_token **token, t_mini *mini, int *i)
{
	char	*segment;
	pid_t	pid;
	char	*value;

	value = NULL;
	if ((*token)->text[*i] == '$')
	{
		pid = fork();
		if (pid != 0)
			segment = ft_itoa(pid);
		else
			exit(0);
		(*i)++;
		return (segment);
	}
	else
	{
		value = get_env_value(mini, "HOME");
		if(!value)
			return("");
		else
			segment = value;
		return (segment);
	}
}
