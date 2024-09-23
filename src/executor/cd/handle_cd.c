/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:02:35 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/23 09:31:51 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dir(t_token *token, char **tgt_dir, t_mini *mini)
{
	if (token->next == NULL
		|| ft_strncmp(token->next->text, "~",
			ft_strlen(token->next->text)) == 0)
	{
		*tgt_dir = get_env_value(mini, "HOME");
		if (!*tgt_dir)
			*tgt_dir = HOME;
	}
	else if (ft_strncmp(token->next->text, "-",
			ft_strlen(token->next->text)) == 0)
	{
		if (mini->prev_dir == NULL)
			*tgt_dir = mini->curr_dir;
		else
			*tgt_dir = mini->prev_dir;
	}
	else if (ft_strncmp(token->next->text, "..", 2) == 0)
		*tgt_dir = "..";
	else if (ft_strncmp(token->next->text, ".", 1) == 0)
		*tgt_dir = mini->curr_dir;
	else
		*tgt_dir = token->next->text;
}

void	handle_cd2(t_mini *mini, char *target_dir)
{
	free(mini->prev_dir);
	mini->prev_dir = ft_strdup(mini->curr_dir);
	if (target_dir == mini->curr_dir)
	{
		handle_pwd(mini);
		mini->return_code = 0;
	}
}

void	handle_cd(t_token *token, t_mini *mini)
{
	char	*target_dir;

	if (count_nodes(token) > 2)
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_TARG), token->text);
		mini->return_code = 1;
		return ;
	}
	if (token->next)
		expander(&token->next, mini);
	handle_dir(token, &target_dir, mini);
	if (check_dir(target_dir))
	{
		if (chdir(target_dir) != 0 && token->next)
		{
			ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_CD), token->next->text);
			mini->return_code = 1;
		}
		else
			handle_cd2(mini, target_dir);
	}
}
