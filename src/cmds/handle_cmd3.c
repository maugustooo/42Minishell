/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:07:11 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/23 12:15:14 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_cmd3(t_token **token, t_mini *mini, char **args)
{
	if (access((*token)->text, F_OK) == -1)
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_CD), (*token)->text);
		free_child(token, mini, args);
		exit(127);
	}
	if (check_access((*token)->text))
		return (check_file(args, token, mini));
	else
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_PERMS), (*token)->text);
		free_child(token, mini, args);
		exit(126);
	}
}

int	handle_cmd3_5(t_token *temp, t_token **token, t_mini *mini, char **args)
{
	int		ret;
	int		i;

	i = -1;
	while (temp)
	{
		args[++i] = ft_strdup(temp->text);
		temp = temp->next;
	}
	args[++i] = NULL;
	ret = handle_cmd2(token, mini, args);
	free_args(args);
	return(ret);
}
