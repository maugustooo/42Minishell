/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:02:35 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/02 11:08:38 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles directory change
 * 
 * @param next Argument
 * @param target_dir Target Directory
 * @param prev_dir Pointer to previous directory
*/
void	handle_dir(t_token *next, char **target_dir, char **prev_dir)
{
    if (next->next->text == NULL 
	|| ft_strncmp(next->next->text, "~", ft_strlen(next->next->text)) == 0)
        {
            *target_dir = getenv("HOME");
            if (!*target_dir)
                *target_dir = HOME;
        }
        else if (ft_strncmp(next->next->text, "-",
		 ft_strlen(next->next->text)) == 0)
        {
            if (*prev_dir == NULL)
                *target_dir = HOME;
            else
                *target_dir = *prev_dir;
        }
        else
            *target_dir = next->next->text;
	// else
	// 	//TODO: NO PATH FOUND
}

/**
 * @brief Handles cd command
 * 
 * @param arg Argument
 * @param prev_dir Pointer to handle previous directory
*/
void	handle_cd(t_token *arg, char **prev_dir)
{
    char    *target_dir;
    char    current_dir[MAX_PATH_LEN];

    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
    {
        //TODO: HANDLE ERROR
        return;
    }
    handle_dir(arg, &target_dir, prev_dir);
    if (chdir(target_dir) != 0)
	{
        //TODO: HANDLE ERROR
		ft_printf("\n");
	}
    else
    {
        free(*prev_dir);
        *prev_dir = ft_strdup(current_dir);
    }    
}
