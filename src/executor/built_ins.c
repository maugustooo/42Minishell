/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:18:29 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/30 10:04:25 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file built_ins.c
 * @brief Handle built ins
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

void	handle_dir(t_token *next, char *target_dir, char *prev_dir)
{
    if (next == NULL || ft_strcmp(next, "~", ft_strlen(next)) == 0)
        {
            target_dir = getenv("HOME");
            if (!target_dir)
                target_dir = HOME;
        }
        else if (ft_strncmp(next, "-", ft_strlen(next)) == 0)
        {
            if (prev_dir == NULL)
                target_dir = HOME;
            else
                target_dir = prev_dir;
        }
        else
            target_dir = next;
}

/**
 * @brief Handle the exit
 * 
 * @param prev_dir Free previous_dir
*/
void	handle_exit(char *prev_dir)
{
    //TODO: Free list
    free(prev_dir);
    exit(0);
}

/**
 * @brief Handles the built in functions (cd and exit)
 * 
 * @param token Command
 * @param next Arguments
*/
void	handle_built_in(t_token *token, t_token *next)
{
    char *prev_dir = NULL;

    if (ft_strncmp(token, "cd", ft_strlen(token)) == 0)
    {
        char    *target_dir;
        char    current_dir[MAX_PATH_LEN];

        if (getcwd(current_dir, sizeof(current_dir)) == NULL)
        {
            //TODO: HANDLE ERROR
            return;
        }
        handle_dir(next, &target_dir, &prev_dir);
        if (chdir(target_dir) != 0)
            //TODO: HANDLE ERROR
        else
        {
            free(prev_dir);
            prev_dir = ft_strdup(current_dir);
        }
    }
    else if (ft_strncmp(token, "exit", ft_strlen(token)) == 0)
        handle_exit(&prev_dir);
}

/**@}*/