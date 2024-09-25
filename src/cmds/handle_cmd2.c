/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:27:56 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/25 13:42:30 by maugusto         ###   ########.fr       */
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
		return(handle_cmd3(token, mini, args));
	else
		return (handle_cmd2_5(token, mini, args));
}

int	check_command2(char *full_path, char **dirs, t_token **token, t_mini *mini)
{
	int	i;

	i = 0;
	while (dirs[i] != NULL)
	{
		full_path = build_full_path(dirs[i], (*token)->text, mini);
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

int	check_file2(char **args, t_token **token, t_mini *mini)
{
	args[0] = ft_strdup((*token)->text);
	// print_tokens(*token, mini);
	handle_redirection(args, mini, *token);
	// int o = 0;
	// while (args[o])
	// {
	// 	ft_printf("args[%d]:%s\n", o, args[o]);
	// 	o++;
	// }
	if (execve((*token)->text, args, mini->penv) == -1)
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_CMD),
			(*token)->text);
		return (0);
	}
	return (1);
}

