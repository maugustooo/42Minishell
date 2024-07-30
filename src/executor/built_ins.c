/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:18:29 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/29 16:03:11 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file built_ins.c
 * @brief Handle built ins
*/

#include "minishell.h"

int is_built_in(t_token *token)
{
    return(token->type == CMD);
    // return(ft_strncmp(cmd, "cd", ft_strlen(cmd)) 
    // || ft_strncmp(cmd, "exit", ft_strlen(cmd)));
}

void    handle_built_in(t_token *token, t_token *next)
{
    if(ft_strncmp(token->line, "cd", ft_strlen(token->line)) == 0)
    {
        if(next == NULL)
            ft_printf(stderr, "Expected argument")
        else
        {
            if(chdir(next) != 0)
                //HANDLE ERROR
        }
    }
    else if (ft_strncmp(token->line, "exit", ft_strlen(token->line)) == 0)
        exit(EXIT_SUCCESS);
}

/**@}*/