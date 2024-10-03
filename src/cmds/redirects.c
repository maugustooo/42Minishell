/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:29:22 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/03 15:40:25 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	move_left_args(char **args, int *i, char *last_text)
{
	int	j;

	j = *i - 1;
	if (ft_strcmp(args[*i], last_text) != 0)
	{
		while (args[j + 2])
		{
			args[j] = args[j + 2];
			j++;
		}
		args[j] = NULL;
		args[j + 1] = NULL;
	}
	*i -= 2;
}

static int	handle_single_redirection(char **args, t_mini *mini)
{
	int	i;
	int	file;

	file = 0;
	i = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "<") && args[i] && ft_strcmp(args[i], "|") != 0)
		{
			i++;
			if (!handle_input(&args, &i, mini))
				return (0);
			file = 1;
		}
		else if (((ft_strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0))
			&& args[i] && ft_strcmp(args[i], "|") != 0)
		{
			if (!handle_output(&args, &i, mini))
				return (0);
			file = 1;
		}
		else if (ft_strcmp(args[i], "<<") == 0 && args[i]
			&& ft_strcmp(args[i], "|") != 0)
			handle_heredoc(&args, &i, mini);
		else
			i++;
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
		t_token *last_red)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	i--;
	while (i > 0)
	{
		if ((ft_strcmp(args[i - 1], "<") == 0 || ft_find_c('<', args[i])))
		{
			if (ft_strcmp(args[i], "<") != 0 && ft_strcmp(args[i], "<<") != 0)
			{
				if (!check_file_red(args[i]))
					return (0);
				else
				{
					if (!handle_input(&args, &i, mini))
						return (0);
					i --;
				}
			}
		}
		if (!ft_strcmp(args[i - 1], "<") && args[i] && mini)
			move_left_args(args, &i, last_red->next->text);
		else if ((!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], ">>"))
			&& args[i + 1])
			move_left_args(args, &i, last_red->next->text);
		else
			i--;
	}
	return (1);
}

void	handle_redirection(char **args, t_mini *mini, t_token **token)
{
	t_token	*last_redirect;

	count_redirections(*token, mini);
	last_redirect = ft_tokenlast_redirect(*token);
	if (mini->input_count > 1 || mini->output_count > 1
		|| mini->append_count > 1)
	{
		if (!handle_mult_redirections(args, mini, last_redirect))
		{
			free_child(token, mini, args);
			mini->return_code = 2;
			exit (2);
		}
		remove_redirection_symbol(args);
	}
	else
	{
		if (!handle_single_redirection(args, mini))
		{
			free_child(token, mini, args);
			exit (1);
		}
		remove_redirection_symbol(args);
	}
}
