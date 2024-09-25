/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:18:55 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/25 15:29:09 by maugusto         ###   ########.fr       */
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
			handle_exit_conditions(Error_Msg(ERROR_PERMS), token, mini, args);
	}
	else if (S_ISDIR(path_stat.st_mode))
		handle_exit_conditions(Error_Msg(ERROR_ISDIR), token, mini, args);
	else
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_CD), (*token)->text);
	return (0);
}

char	*build_full_path(char *dir, const char *cmd, t_mini *mini)
{
	char	*full_path;
	int		dir_len;
	int		cmd_len;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	full_path = malloc(dir_len + cmd_len + 2);
	if (!full_path)
		error_malloc(mini);
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
	free(value);
	free(key);
	if (check_command2(full_path, dirs, token, mini) == 1)
		return (check_file(args, token, mini));
	free_keys(&dirs);
	return (0);
}

int handle_cmd(t_token **token, t_mini *mini)
{	
	char	**args;
	t_token	*temp;

	temp = *token;
	args = ft_calloc(mini->token_count + 1, sizeof(char *));
	if (!args)
		error_malloc(mini);
	expander(token, mini);
	g_pid = fork();
	if (g_pid == 0)
		handle_cmd3_5(temp, token, mini, args);
	free_args(args);
	return (0);
}

int 	handle_cmd_pipe(t_token **token, t_mini *mini)
{
	int		i;
	char	**args;
	t_token	*temp;
	int		ret;

	i = -1;
	temp = *token;
	args = ft_calloc(mini->token_count + 1, sizeof(char *));
	if (!args)
		error_malloc(mini);
	expander(token, mini);
	while (temp && temp->type != PIPE)
	{
		args[++i] = ft_strdup(temp->text);
		temp = temp->next;
	}
	args[++i] = NULL;
	ret = handle_cmd2(token, mini, args);
	free_args(args);
	return(ret);	
}
