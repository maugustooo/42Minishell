/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:27:56 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/17 10:56:27 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_cmd2_5(t_token **token, t_mini *mini, char **args)
{
	if (!check_command(token, mini, args))
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_CMD), (*token)->text);
		free_child(token, mini, args);
		exit(127);
	}
	else
		return (check_file(args, token, mini));
}

int	handle_cmd2(t_token **token, t_mini *mini, char **args)
{
	if(ft_strcmp((*token)->text, "") == 0 && (*token)->next == NULL)
	{
		free_child(token, mini, args);
		exit(0);
	}
	if(ft_strcmp((*token)->text, "") == 0 && (*token)->next != NULL)
	{
		(*token) = (*token)->next;
		(*token)->type = 1;
	}
	if(is_built_in(*token))
		return(executor(token, mini), 0);
	else if (ft_strncmp((*token)->text, "/", 1) == 0
		|| ft_strncmp((*token)->text, "./", 2) == 0)
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
	else
		return (handle_cmd2_5(token, mini, args));
}

int	check_command2(char *full_path, char **dirs, t_token **token)
{
	int	i;

	i = 0;
	while (dirs[i] != NULL)
	{
		full_path = build_full_path(dirs[i], (*token)->text);
		if (!full_path)
			return (0);
		if (check_access(full_path))
		{
			change_token_text(*token, full_path);
			free_keys(&dirs);
			return (1);
		}
		free(full_path);
		i++;
	}
	return (0);
}

void handle_redirection(char **args)
{
	int i;

	i = 0;
    while (args[i])
	{
        if (ft_strcmp(args[i], "<") == 0 && args[i] && ft_strcmp(args[i], "|") != 0)
		{
            if(!handle_input(&args, &i))
				break ;
		}
		else if ((ft_strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0)
			&& args[i] && ft_strcmp(args[i], "|") != 0)
		{
			if(!handle_output(&args, &i))
				break ;
		}
		else if (ft_strcmp(args[i], "<<") == 0 && args[i] && ft_strcmp(args[i], "|") != 0)
			handle_heredoc(&args, &i);
		else
			i++;
    }
}

int	check_file2(char **args, t_token **token, t_mini *mini)
{
	struct stat	path_stat;
	int			i;

	i = -1;
	args[0] = ft_strdup((*token)->text);
	while (args[++i])
	{
		if (stat(args[i], &path_stat) == 0
			&& S_ISDIR(path_stat.st_mode))
		{
			ft_printf_fd(STDERR_FILENO,
				Error_Msg(ERROR_ISDIR), args[i]);
			return (0);
		}
	}
	handle_redirection(args);
	if (execve((*token)->text, args, mini->penv) == -1)
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_CMD),
			(*token)->text);
		return (0);
	}
	return (1);
}

