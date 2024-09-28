/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:07:11 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/27 17:12:37 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_cmd3(t_token **token, t_mini *mini, char **args)
{
	if (access((*token)->text, F_OK) == -1)
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_CD), (*token)->text);
		free_child(token, mini, args);
		exit(127);
	}
	if (check_access((*token)->text))
		return (check_file(args, token, mini));
	else
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_PERMS), (*token)->text);
		free_child(token, mini, args);
		exit(126);
	}
}

int	handle_cmd3_5(t_token *temp, t_token **token, t_mini *mini, char **args)
{
	int		ret;
	int		i;

	i = -1;
	while (temp)
	{
		expander(&temp, mini);
		if(temp->type == INPUT)
		{
			if(temp->next && temp->next->type == FILE)
			{
				args[++i] = ft_strdup(temp->text);
				temp = temp->next;
			}
			while (temp->type == FILE && temp->next	)
			{
				if(temp->next->type == FILE)
					temp = temp->next;
				else
					break ;
			}
		}
		args[++i] = ft_strdup(temp->text);
		temp = temp->next;
	}
	args[++i] = NULL;
	ret = handle_cmd2(token, mini, args);
	free_args(args);
	return(ret);
}

char	**change_args_exec(char **args, t_token *token, t_mini *mini)
{
	char	**key;
	char	**nargs;
	int 	i;
	int		j;

	i = -1;
	key = ft_split(token->text, ' ');
	j = ft_arrlen(args) + ft_arrlen(key);
	nargs = ft_calloc(j, sizeof(char **));
	if(!nargs)
		error_malloc(mini);
	while(key[++i])
		nargs[i] = ft_strdup(key[i]);
	j = 0;
	i--;
	while(nargs[j++ + i] && args[j])
		nargs[i + j] = ft_strdup(args[j]);
	nargs[i + j] = NULL;
	free_keys(&key);
	free_args(args);
	return (nargs);
}
