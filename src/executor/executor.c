/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:29:20 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/31 12:33:16 by maugusto         ###   ########.fr       */
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

/**
 * @brief Handles the built in functions
 * 
 * @param token Command
 * @param next Arguments
*/
void    executor(t_token **token)
{
    char *prev_dir = NULL;

    if (is_built_in(*token))
    {
        if (ft_strncmp((*token)->text, "cd", ft_strlen((*token)->text)) == 0)
            handle_cd(*token, &prev_dir);
        else if (ft_strncmp((*token)->text, "echo", ft_strlen((*token)->text)) == 0)
            handle_echo((*token)->next->text, (*token)->next->next);
		else if (ft_strncmp((*token)->text, "env", ft_strlen((*token)->text)) == 0)
			handle_env((*token)->next);
		else if (ft_strncmp((*token)->text, "pwd", ft_strlen((*token)->text)) == 0)
			handle_pwd();
        else if (ft_strncmp((*token)->text, "exit", ft_strlen((*token)->text)) == 0)
            handle_exit(&prev_dir);
    }
    else
    {
        
    }
}

/**@}*/