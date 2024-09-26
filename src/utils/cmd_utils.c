/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:05:42 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/26 15:22:45 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path(t_mini *mini)
{
	char	*checker;

	checker = get_env_key(mini, "PATH");
	if (checker == NULL)
		return (0);
	return (1);
}

int	check_access(char *full_path)
{
	struct stat	path_stat;

	if (stat(full_path, &path_stat) == 0 && access(full_path, X_OK) == 0)
		return (1);
	return (0);
}

void	free_child(t_token **token, t_mini *mini, char **args)
{
	if(args)
		free_args(args);
	freethem(token, mini);
	free_things(mini);
}

void	error_malloc(t_mini *mini)
{
	ft_printf_fd(STDERR_FILENO, "MALLOC ERROR\n");
	mini->return_code = 137;
	exit(137);
}

void	handle_exit_conditions(const char *msg, t_token **token, t_mini *mini,
	char **args)
{
	ft_printf_fd(STDERR_FILENO, msg, (*token)->text);
	free_child(token, mini, args);
	exit(126);
}
