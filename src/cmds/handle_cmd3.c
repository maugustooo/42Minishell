/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:07:11 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/03 12:34:38 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_cmd3(t_token **token, t_mini *mini, char **args)
{
	if (access((*token)->text, F_OK) == -1)
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_NFILE), (*token)->text);
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

void	change_token_args(t_token *token, char **key, t_mini *mini)
{
	t_token *curr;
	t_token	*new_token;
	int 	i;

	i = 0;
	curr = token;
	while (key[i])
	{
		if (i == 0)
		{
			free(curr->text);
			curr->text = ft_strdup(key[i]);
		}
		else
		{
			new_token = (t_token *)malloc(sizeof(t_token));
			if(!new_token)
				error_malloc(mini);
			new_token->text = ft_strdup(key[i]);
			new_token->next = curr->next;
			curr->next = new_token;
			curr = new_token;
		}
		i++;
	}
}

char	**change_args_exec(char **args, t_token *token, t_mini *mini)
{
	char	**key;
	char	**nargs;
	size_t 	i;
	size_t	j;
	int		total_len;

	key = ft_split(token->text, ' ');
	change_token_args(token, key, mini);
	total_len = ft_arrlen(args) + ft_arrlen(key);
	nargs = ft_calloc(total_len + 1, sizeof(char **));
	if(!nargs)
		error_malloc(mini);
	i = -1;
	while (++i < ft_arrlen(key))
	{
		nargs[i] = ft_strdup(key[i]);
		if(!nargs[i])
			error_malloc(mini);
	}
	j = 1;
	while(j < ft_arrlen(args))
	{
		nargs[i++] = ft_strdup(args[j++]);
		if(!nargs[i - 1])
			error_malloc(mini);
	}
	nargs[i] = NULL;
	// while(key[++i])
	// 	nargs[i] = ft_strdup(key[i]);
	// j = 0;
	// i--;
	// while(nargs[j++ + i] && args[j])
	// 	nargs[i + j] = ft_strdup(args[j]);
	// nargs[i + j] = NULL;
	free_keys(&key);
	free_args(args);
	return (nargs);
}
