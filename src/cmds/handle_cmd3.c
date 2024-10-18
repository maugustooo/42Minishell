/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:07:11 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/18 12:15:19 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_cmd3(t_token **token, t_mini *mini, char **args)
{
	if (access((*token)->text, F_OK) == -1)
	{
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_NFILE), (*token)->text);
		free_child(token, mini, args);
		exit(127);
	}
	if (check_access((*token)->text))
		return (check_file(args, token, mini));
	else
	{
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_PERMS), (*token)->text);
		free_child(token, mini, args);
		exit(126);
	}
}

int	advance_token(t_token *temp)
{
	while (temp->next && (temp->type == FILE
			|| (temp->next->type == FILE
			|| temp->next->type == NFILE)))
	{
		if (temp->next->type == FILE)
			temp = temp->next;
		else if (temp->type == FILE && temp->next->type != FILE)
			return (1);
		else
			return (0);
	}
	return (1);
}

int	handle_cmd3_5(t_token *temp, t_token **token, t_mini *mini, char **args)
{
	int		ret;
	int		i;

	i = -1;
	while (temp)
	{
		if (temp->type == INPUT)
		{
			if (temp->next && temp->next->type == FILE)
			{
				args[++i] = ft_strdup(temp->text);
				temp = temp->next;
			}
			if (!advance_token(temp))
				break ;
		}
		if (ft_strcmp(temp->text, "") != 0)
			args[++i] = ft_strdup(temp->text);
		temp = temp->next;
	}
	args[++i] = NULL;
	ret = handle_cmd2(token, mini, args);
	return (ret);
}

void	change_token_args(t_token *token, char **key, t_mini *mini)
{
	t_token	*curr;
	t_token	*new_token;
	int		i;

	i = -1;
	curr = token;
	while (key[++i])
	{
		if (i == 0)
		{
			free(curr->text);
			curr->text = ft_strdup(key[i]);
		}
		else if (key[i])
		{
			new_token = (t_token *)malloc(sizeof(t_token));
			if (!new_token)
				error_malloc(mini);
			new_token->text = ft_strdup(key[i]);
			new_token->type = 2;
			new_token->next = curr->next;
			curr->next = new_token;
			curr = new_token;
		}
	}
}

char	**change_args_exec(char **args, t_token *token, t_mini *mini)
{
	char	**nargs;

	if (token && ft_find_c(' ', token->text))
		return(args);
	expander(&token, mini);
	nargs = create_nargs(token, args, mini);
	copy_args(nargs, args, mini, ft_arrlen(nargs));
	free_args(args);
	return (nargs);
}
