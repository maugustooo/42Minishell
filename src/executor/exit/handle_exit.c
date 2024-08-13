/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:06:31 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/13 10:46:37 by gude-jes         ###   ########.fr       */
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
void    handle_exit(t_token **token, t_mini *mini)
{
    //TODO: FREE LIST
	free_penv(mini);
	freethem(token, mini);
    exit(EXIT_SUCCESS);
}

/**@}*/