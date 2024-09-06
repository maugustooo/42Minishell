/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:02:35 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/06 08:56:54 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles directory change
 * 
 * @param next Argument
 * @param tgt_dir Target Directory
 * @param mini Struct of minishel
 * @param curr_dir Current directory
*/
void	handle_dir(t_token *next, char **tgt_dir, t_mini *mini, char *curr_dir)
{
    if (next->next == NULL 
	|| ft_strncmp(next->next->text, "~", ft_strlen(next->next->text)) == 0)
        {
            *tgt_dir = getenv("HOME");
            if (!*tgt_dir)
				*tgt_dir = HOME;
		}
		else if (ft_strncmp(next->next->text, "-", ft_strlen(next->next->text)) == 0)
		{
			if (mini->prev_dir == NULL)
				*tgt_dir = curr_dir;
            else
				*tgt_dir = mini->prev_dir;
		}
		else if (ft_strncmp(next->next->text, "..", 2) == 0)
			*tgt_dir = "..";
		else if (ft_strncmp(next->next->text, ".", 1) == 0)
			*tgt_dir = curr_dir;
		else
			*tgt_dir = next->next->text;
}

/**
 * @brief Handles cd command
 * 
 * @param token Token Struct
 * @param mini Minishell Struct
*/
void	handle_cd(t_token *token, t_mini *mini)
{
	char    *target_dir;
	char    current_dir[MAX_PATH_LEN];

	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		//TODO: HANDLE ERROR
		return;
	}
	if(count_nodes(token) > 2)
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_TARG), token->text);
		mini->return_code = 1;
		return ;
	}
	if(token->next)
		expander(&token->next, mini);
	handle_dir(token, &target_dir, mini, current_dir);
	if (chdir(target_dir) != 0 && token->next)
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_CD), token->next->text);
		mini->return_code = 1;
		ft_printf("\n");
	}
	else
	{
		free(mini->prev_dir);
		mini->prev_dir = ft_strdup(current_dir);
		if(target_dir == current_dir)
		{
			handle_pwd(mini);
			mini->return_code = 0;
		}
	}
}
