/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:34:17 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/10 08:54:51 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pwd(t_mini *mini, t_token *token)
{
	if (token->next && (token->next->type != PIPE || token->next->text[0] == '-'))
	{
		ft_printf_fd(STDERR_FILENO, "pwd: options not allowed\n");
		mini->return_code = 1;
		return (1);
	}
	return (0);
}

void	handle_pwd(t_mini *mini, t_token *token)
{
	char	cwd[MAX_PATH_LEN];

	if(check_pwd(mini, token))
		return;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_printf("%s\n", cwd);
		mini->return_code = 0;
	}
	else
	{
		if (ft_strcmp(mini->curr_dir, "") == 0)
		{
			ft_printf_fd(STDERR_FILENO, "Computer Error");
			mini->return_code = 1;
		}
		else
		{
			ft_printf("%s\n", mini->curr_dir);
			mini->return_code = 0;
		}
	}
}
