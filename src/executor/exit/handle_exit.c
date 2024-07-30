/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:06:31 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/30 15:23:55 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file handle_exit.c
 * @brief Handles the exit
*/

#include "minishell.h"

/**
 * @brief Handles the exit command
 * 
 * @param prev_dir Free previous_dir
*/
void    handle_exit(char *prev_dir)
{
    //TODO: FREE LIST
    free(prev_dir);
    exit(EXIT_SUCCESS);
}

/**@}*/