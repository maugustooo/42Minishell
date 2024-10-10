/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:46:26 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/10 08:48:39 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if token is command
 * 
 * @param token Token
 * @return int 1 or 0
*/
int	is_built_in(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == CMD
		&& (ft_strcmp(token->text, "cd") == 0
			|| ft_strcmp(token->text, "echo") == 0
			|| ft_strcmp(token->text, "env") == 0
			|| ft_strcmp(token->text, "pwd") == 0
			|| ft_strcmp(token->text, "export") == 0
			|| ft_strcmp(token->text, "unset") == 0
			|| ft_strcmp(token->text, "exit") == 0));
}

void	handle_built_ins(t_token **token, t_mini *mini)
{
	if (ft_strncmp((*token)->text, "echo", 4) == 0)
		handle_echo(token, mini);
	else if (ft_strncmp((*token)->text, "cd", 2) == 0)
		handle_cd(*token, mini);
	else if (ft_strncmp((*token)->text, "env", 3) == 0)
		handle_env(mini, *token);
	else if (ft_strncmp((*token)->text, "pwd", 3) == 0)
		handle_pwd(mini, *token);
	else if ((ft_strncmp((*token)->text, "export", 6) == 0))
		handle_export(mini, (*token)->next);
	else if (ft_strncmp((*token)->text, "unset", 5) == 0)
		handle_unset(*token, mini);
	else if (ft_strncmp((*token)->text, "exit", 4) == 0)
		handle_exit(token, mini);
}

/**
 * @brief Handles the built in functions
 * 
 * @param token Command
 * @param next Arguments
*/
void	executor(t_token **token, t_mini *mini)
{
	int	status;

	if (is_built_in(*token) && !mini->pipe)
		handle_built_ins(token, mini);
	else if (!mini->pipe)
	{
		status = handle_cmd(token, mini);
		if (WIFEXITED(status))
			mini->return_code = WEXITSTATUS(status);
	}
	else
		pipes(token, mini);
}
