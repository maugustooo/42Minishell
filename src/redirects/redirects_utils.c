/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:16:07 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/14 12:17:59 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_and_heredoc(char *str)
{
	return (ft_strcmp(str, "<") != 0 && ft_strcmp(str, "<<") != 0);
}

int	output_or_append(char *str)
{
	return (!ft_strcmp(str, ">") || ft_strcmp(str, ">>"));
}

void	move_left_args(char **args, int *i, char *last_text)
{
	int	j;

	j = *i - 1;
	if (ft_strcmp(args[*i], last_text) != 0)
	{
		while (args[j + 2])
		{
			args[j] = args[j + 2];
			j++;
		}
		args[j] = NULL;
		args[j + 1] = NULL;
	}
	*i -= 2;
}

int	args_len(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	i --;
	return (i);
}

int condition_hereoc(char *buffer, char *delimiter)
{
	return (ft_strncmp(buffer, delimiter, ft_strlen(delimiter)) == 0
			&& buffer[ft_strlen(delimiter)] == '\n');
}