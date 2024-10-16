/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:12:45 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/16 11:51:55 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_ss_dolla(t_token **token, t_mini *mini, char *segment, int *i)
{
	pid_t	pid;

	pid = fork();
	if (pid != 0)
	{
		segment = ft_itoa(pid);
		waitpid(pid, NULL, 0);
	}
	else
	{
		free(mini->result);
		free_child(token, mini, NULL);
		exit(0);
	}
	(*i)++;
	return (segment);
}

char	*handle_special_signs2(t_token **token, t_mini *mini, int *i)
{
	char	*segment;
	char	*value;

	value = NULL;
	segment = NULL;
	if ((*token)->text[*i] == '$')
		segment = handle_ss_dolla(token, mini, segment, i);
	else if ((*token)->text[*i - 1] == '~')
	{
		value = get_env_value(mini, "HOME");
		if (value)
			segment = value;
	}
	return (segment);
}
