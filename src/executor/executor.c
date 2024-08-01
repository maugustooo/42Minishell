/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:29:20 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/01 11:42:26 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/**
 * @defgroup mandatory Mandatory
 * @{
 * @file executor.c
 * @brief Executor of minishell
 * 
*/

#include "minishell.h"

/**
 * @brief Checks if token is command
 * 
 * @param token Token
 * @return int 1 or 0
*/
int	is_built_in(t_token *token)
{
    return(token->type == CMD);
}

void	handle_built_ins(t_token **token)
{
	static char *prev_dir = NULL;
	
	if (ft_strncmp((*token)->text, "cd", 2) == 0)
		handle_cd(*token, &prev_dir);
	else if (ft_strncmp((*token)->text, "echo", 4) == 0)
		handle_echo((*token)->next->text, (*token)->next);
	else if (ft_strncmp((*token)->text, "env", 3) == 0)
		handle_env((*token)->next);
	else if (ft_strncmp((*token)->text, "pwd", 3) == 0)
		handle_pwd();
	else if ((ft_strncmp((*token)->text, "export", 6) == 0))
		handle_export();
	// else if (ft_strncmp((*token)->text, "unset", 5) == 0)
	// 	handle_unset();
	else if (ft_strncmp((*token)->text, "exit", 4) == 0)
		handle_exit(&prev_dir);
}

/**
 * @brief Handles the built in functions
 * 
 * @param token Command
 * @param next Arguments
*/
void    executor(t_token **token)
{
	
    if (is_built_in(*token))
    {
		handle_built_ins(token);
    }
    else
    {
        
    }
}

/**@}*/