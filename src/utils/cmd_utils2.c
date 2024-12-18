/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:07:29 by gude-jes          #+#    #+#             */
/*   Updated: 2024/11/04 09:07:29 by gude-jes         ###   ########.fr       */
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
		if (access(token->text, W_OK) == 0)
			return (0);
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_ISDIR), token->text);
		return (1);
	}
	return (1);
}

int	check_file_red(char *file)
{
	struct stat	path_stat;

	if (stat(file, &path_stat) == -1)
	{
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_NFILE), file);
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

	if (ft_strcmp(token->text, "") == 0 && token->next)
		token = token->next;
	key = ft_split(token->text, ' ');
	change_token_args(token, key, mini);
	total_len = ft_arrlen(args) + ft_arrlen(key);
	nargs = ft_calloc(total_len + 1, sizeof(char *));
	if (!nargs)
		error_malloc(mini);
	i = -1;
	while (key[++i])
	{
		if (ft_isdigitloop(key[i]))
			nargs[i] = ft_itoa(ft_atoi(key[i]));
		else
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
	while (args[i])
	{
		if (args[i])
			nargs[start++] = ft_strdup(args[i]);
		if (!nargs[start - 1])
			error_malloc(mini);
		i++;
	}
	nargs[start] = NULL;
}

char	*last_delimiter(char **args)
{
	char	**tmp;
	int		j;
	char	*delimiter;

	delimiter = NULL;
	j = 0;
	tmp = args;
	while (tmp[j])
	{
		if (ft_strcmp(tmp[j], "<<") == 0)
		{
			if (tmp[j + 1])
				delimiter = tmp[j + 1];
		}
		j++;
	}
	return (delimiter);
}
