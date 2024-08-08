/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:02:35 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/08 14:31:32 by maugusto         ###   ########.fr       */
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
void	handle_dir(t_token *next, char **target_dir, t_mini *mini)
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
			if (mini->prev_dir == NULL)
				*target_dir = HOME;
            else
				*target_dir = mini->prev_dir;
		}
		else
			*target_dir = next->next->text;
}

/**
 * @brief Handles cd command
 * 
 * @param arg Argument
 * @param prev_dir Pointer to handle previous directory
*/
void	handle_cd(t_token *arg, t_mini *mini)
{
	char    *target_dir;
	char    current_dir[MAX_PATH_LEN];

	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		//TODO: HANDLE ERROR
		return;
	}
	if(arg->next)
		handle_dir(arg, &target_dir, mini);
	if (chdir(target_dir) != 0 && arg->next)
	{
		ft_printf(Error_Msg(ERROR_CD), arg->next->text);
		ft_printf("\n");
	}
	else
	{
		free(mini->prev_dir);
		mini->prev_dir = ft_strdup(current_dir);
	}
}
