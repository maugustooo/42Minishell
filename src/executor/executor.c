/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:29:20 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/30 15:33:35 by gude-jes         ###   ########.fr       */
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
void    executor(t_token *token, t_token *next)
{
    char *prev_dir = NULL;

    if (is_built_in(token))
    {
        if (ft_strncmp(token, "cd", ft_strlen(token)) == 0)
            handle_cd(next, &prev_dir);
        else if (ft_strncmp(token, "echo", ft_strlen(token)) == 0)
            handle_echo(next, next->next);
        else if (ft_strncmp(token, "exit", ft_strlen(token)) == 0)
            handle_exit(&prev_dir);
        //handle_built_in(token, next);
    }
    else
    {
        
    }
}

/**@}*/