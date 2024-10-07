/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:13:27 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/07 11:22:00 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file_perms(t_token *token)
{
	struct stat	path_stat;

	if (stat(token->text, &path_stat) == -1)
		return (1);
	if (S_ISREG(path_stat.st_mode))
	{
		if (access(token->text, W_OK) != 0)
			return (0);
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_ISDIR), token->text);
		return (1);
	}
	return (1);
}

int	check_file_red(char *file)
{
	struct stat	path_stat;

	if (stat(file, &path_stat) == -1)
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_NFILE), file);
		return (0);
	}
	if (S_ISREG(path_stat.st_mode))
	{
		if (access(file, R_OK | X_OK) == 0)
			return (1);
	}
	return (1);
}

char	**create_nargs(t_token *token, char **args, t_mini *mini)
{
	char	**key;
	char	**nargs;
	size_t	i;
	int		total_len;

	key = ft_split(token->text, ' ');
	change_token_args(token, key, mini);
	total_len = ft_arrlen(args) + ft_arrlen(key);
	nargs = ft_calloc(total_len + 1, sizeof(char *));
	if (!nargs)
		error_malloc(mini);
	i = -1;
	while (key[++i])
	{
		nargs[i] = ft_strdup(key[i]);
		if (!nargs[i])
			error_malloc(mini);
	}
	free_keys(&key);
	return (nargs);
}

void	copy_args(char **nargs, char **args, t_mini *mini, size_t start)
{
	size_t	i;

	i = 1;
	while (args[i++])
	{
		nargs[start++] = ft_strdup(args[i]);
		if (!nargs[start - 1])
			error_malloc(mini);
	}
	nargs[start] = NULL;
}