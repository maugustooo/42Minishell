/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:11:42 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/24 12:21:10 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dir(char *tgt_dir)
{
	struct stat	path_stat;

	if (!tgt_dir)
	{
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_HOME), tgt_dir);
		return (0);
	}
	if (stat(tgt_dir, &path_stat) == -1)
	{
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_CD), tgt_dir);
		return (0);
	}
	if (!S_ISDIR(path_stat.st_mode))
	{
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_CD), tgt_dir);
		return (0);
	}
	if (access(tgt_dir, R_OK | X_OK) == -1)
	{
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_PERMS), tgt_dir);
		return (0);
	}
	return (1);
}

void	cd_env_pwd(t_mini *mini)
{
	char	*new_pwd;
	char	*pwd;
	int		i;
	char	cwd[MAX_PATH_LEN];

	pwd = get_env_key(mini, "PWD");
	if (!pwd)
	{
		free(pwd);
		return ;
	}
	new_pwd = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	getcwd(mini->curr_dir, sizeof(mini->curr_dir));
	i = 0;
	while (mini->penv[i])
	{
		if (ft_strncmp(mini->penv[i], "PWD=", 4) == 0)
		{
			free(mini->penv[i]);
			mini->penv[i] = new_pwd;
		}
		i++;
	}
	free(pwd);
}

void	cd_env(t_mini *mini)
{
	char	*nold_pwd;
	char	*temp;
	int		i;

	i = 0;
	nold_pwd = get_env_key(mini, "OLDPWD");
	if (!nold_pwd)
	{
		free(nold_pwd);
		return ;
	}
	while (mini->penv[i++])
	{
		if (ft_strncmp(mini->penv[i], "OLDPWD=", 7) == 0)
		{
			free(mini->penv[i]);
			temp = ft_strjoin("OLDPWD=", mini->prev_dir);
			mini->penv[i] = ft_strdup(temp);
			free(temp);
			break ;
		}
	}
	cd_env_pwd(mini);
	free(nold_pwd);
}
