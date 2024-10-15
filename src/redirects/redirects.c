/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:29:22 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/15 14:32:00 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_left_heredoc(char **args, int start_index)
{
	int	i;

	i = start_index;
	while (args[i + 1])
	{
		if (args[i])
			free(args[i]);
		args[i] = args[i + 1];
		i++;
	}
	if (args[i])
		free(args[i]);
	args[i] = NULL;
	i = start_index;
	while (args[i + 1])
	{
		args[i] = args[i + 1];
		i++;
	}
	args[i] = NULL;
}

static int	handle_single_redirection(char **args, t_mini *mini,
		t_redirection_data data)
{
	while (args[data.i])
	{
		if (!ft_strcmp(args[data.i], "<") && args[data.i]
			&& ft_strcmp(args[data.i], "|") != 0)
		{
			data.i ++;
			if (!handle_input(&args, &data.i, mini))
				return (0);
			data.file = 1;
		}
		else if (((ft_strcmp(args[data.i], ">") == 0
					|| strcmp(args[data.i], ">>") == 0))
			&& args[data.i] && ft_strcmp(args[data.i], "|") != 0)
		{
			if (!handle_output(&args, &data.i, mini))
				return (0);
			data.file = 1;
		}
		else if (args[data.i] && ft_strcmp(args[data.i], "<<") == 0
			&& ft_strcmp(args[data.i], "|") != 0)
			handle_heredoc(&args, &data.i, mini);
		else
			data.i ++;
	}
	return (1);
}

static void	remove_redirection_symbol(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "<"))
			i++;
		else
		{
			args[j] = args[i];
			i++;
			j++;
		}
	}
	args[j] = NULL;
}

static int	handle_mult_redirections(char **args, t_mini *mini,
		t_token *last_red, t_redirection_data data)
{
	data.i = args_len(args);
	while (data.i > 0)
	{
		if ((!ft_strcmp(args[data.i - 1], "<") || ft_find_c('<', args[data.i])))
		{
			if (input_and_heredoc(args[data.i]))
			{
				if (!check_file_red(args[data.i]))
					return (0);
				else
				{
					if (!handle_input(&args, &data.i, mini))
						return (0);
					data.i --;
				}
			}
		}
		if (!ft_strcmp(args[data.i - 1], "<") && args[data.i] && mini)
			move_left_args(args, &data.i, last_red->next->text);
		else if (args[data.i + 1] && output_or_append(args[data.i + 1]))
			handle_output(&args, &data.i, mini);
		else
			data.i--;
	}
	return (1);
}

void	handle_redirection(char **args, t_mini *mini, t_token **token)
{
	t_redirection_data	data;

	ft_memset(&data, 0, sizeof(t_redirection_data));
	count_redirections(*token, mini);
	if (mini->input_count > 1)
	{
		if (!handle_mult_redirections(args, mini, ft_last_redir(*token), data))
		{
			free_child(token, mini, args);
			mini->return_code = 2;
			exit (2);
		}
		mini->redir_handled = 1;
		remove_redirection_symbol(args);
	}
	else
	{
		
		if (!handle_single_redirection(args, mini, data))
		{
			free_child(token, mini, args);
			exit (1);
		}
		mini->redir_handled = 1;
		remove_redirection_symbol(args);
	}
}
