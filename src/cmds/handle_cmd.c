/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:18:55 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/16 10:39:16 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file(char **args, t_token **token, t_mini *mini)
{
	struct stat	path_stat;

	if (stat((*token)->text, &path_stat) == -1)
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_CMD), (*token)->text);
		return (0);
	}
	if (S_ISREG(path_stat.st_mode))
	{
		if (access((*token)->text, X_OK) == 0)
			return (check_file2(args, token, mini));
		else
		{
			ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_PERMS), (*token)->text);
			free_child(token, mini, args);
			exit(126);
		}
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_ISDIR), (*token)->text);
		free_child(token, mini, args);
		exit(126);
	}
	else
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_CD), (*token)->text);
	return (0);
}

char	*build_full_path(char *dir, const char *cmd)
{
	char	*full_path;
	int		dir_len;
	int		cmd_len;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	full_path = malloc(dir_len + cmd_len + 2);
	if (!full_path)
		return (NULL); //TODO: Malloc error
	ft_strncpy(full_path, dir, dir_len + 1);
	full_path[dir_len] = '/';
	ft_strncpy(full_path + dir_len + 1, cmd, cmd_len + 1);
	full_path[dir_len + cmd_len + 1] = '\0';
	return (full_path);
}

int	check_command(t_token **token, t_mini *mini, char **args)
{
	char	*key;
	char	*value;
	char	**dirs;
	char	*full_path;

	full_path = NULL;
	key = get_env_key(mini, "PATH");
	if (!key)
		return (free(key), 0);
	value = get_env_value(mini, "PATH");
	if (!value)
		return (free(value), free(key), 0);
	dirs = ft_split(value, ':');
	if (check_command2(full_path, dirs, token) == 1)
		return (check_file(args, token, mini));
	free_keys(&dirs);
	return (0);
}

int handle_cmd(pid_t pid, t_token **token, t_mini *mini)
{
	int		i;
	char	**args;
	t_token	*temp;
	int		ret;

	i = -1;
	temp = *token;
	args = ft_calloc(mini->token_count + 1, sizeof(char *));
	if (!args)
		return (1); //TODO: Malloc Error
	pid = fork();
	if (pid == 0)
	{
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
	free_args(args);
	return (0);
}
