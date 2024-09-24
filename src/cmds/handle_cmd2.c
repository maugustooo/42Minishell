/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:27:56 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/24 09:55:29 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_cmd2_5(t_token **token, t_mini *mini, char **args)
{
	if (!check_command(token, mini, args))
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_CMD), (*token)->text);
		free_child(token, mini, args);
		exit(127);
	}
	else
		return (check_file(args, token, mini));
}

int	handle_cmd2(t_token **token, t_mini *mini, char **args)
{
	if(ft_strcmp((*token)->text, "") == 0 && (*token)->next == NULL)
	{
		free_child(token, mini, args);
		exit(0);
	}
	if(ft_strcmp((*token)->text, "") == 0 && (*token)->next != NULL)
	{
		(*token) = (*token)->next;
		(*token)->type = 1;
	}
	if(is_built_in(*token))
		return(executor(token, mini), 0);
	else if (ft_strncmp((*token)->text, "/", 1) == 0
		|| ft_strncmp((*token)->text, "./", 2) == 0)
		return(handle_cmd3(token, mini, args));
	else
		return (handle_cmd2_5(token, mini, args));
}

int	check_command2(char *full_path, char **dirs, t_token **token, t_mini *mini)
{
	int	i;

	i = 0;
	while (dirs[i] != NULL)
	{
		full_path = build_full_path(dirs[i], (*token)->text, mini);
		if (!full_path)
			return (0);
		if (check_access(full_path))
		{
			change_token_text(*token, full_path);
			free_keys(&dirs);
			return (1);
		}
		free(full_path);
		i++;
	}
	return (0);
}

void handle_single_redirection(char **args, t_mini *mini, t_token *last_red)
{
	int i;

	i = 0;
    while (args[i])
	{
        if (!ft_strcmp(args[i], "<") && args[i] && ft_strcmp(args[i], "|") != 0)
		{
			i++;
			if(!ft_strcmp(args[i], last_red->next->text) && !mini->redirect)
				if(!handle_output(&args, &i, mini))
					break ;
		}
		else if (((ft_strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0))
				&& args[i] && ft_strcmp(args[i], "|") != 0)
		{
			i++;
			if(!ft_strcmp(args[i], last_red->next->text) && !mini->redirect)
				if(!handle_input(&args, &i, mini))
					break ;
		}
		else if (ft_strcmp(args[i], "<<") == 0 && args[i] && ft_strcmp(args[i], "|") != 0)
			handle_heredoc(&args, &i, mini);
		else
			i++;
    }
}

int find_equal_last(char **args, char *last_text)
{
	int i;
	int count ;

	count = 0;
	i = 0;
	while (args[i])
	{
		if(ft_strcmp(args[i], last_text) == 0)
			count ++;
		i++;
	}
	return (count);
}
void move_left_args(char **args, int start_index, char *last_text)
{
    int i = start_index;
	int count;
	
	count = find_equal_last(args, last_text);
    while (args[i + 1])
	{
		if (ft_strcmp(args[i], last_text) == 0 && count == 1)
		{
			break;
		}
		if(ft_strcmp(args[i], last_text) == 0 && count > 1)
		{
			count --;
			i++;
			continue;
		}
		args[i] = args[i + 1];
		i++;
	}
    args[i] = NULL;
}

int check_dup(char **args, char *last_text)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (args[i])
	{
		if(ft_strcmp(args[i], last_text) == 0 && !flag)
		{
			flag = 1;
			i++;
		}
		if(args[i] && ft_strcmp(args[i], last_text) == 0 && flag)
			args[i] = args[i + 1];
		i++;
	}
	return(i);
}
void handle_mult_redirections(char **args, t_mini *mini, t_token *last_red)
{
	int i;
	int last_red_index = -1;

	i = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "<") && args[i + 1])
		{
			if (!ft_strcmp(args[i + 1], last_red->next->text))
				last_red_index = i;
			i += 2;
		}
		else if (((!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], ">>")) && args[i + 1]))
		{
			if (!ft_strcmp(args[i + 1], last_red->next->text))
				last_red_index = i;
			handle_input(&args, &i, mini);
		}
		else if (ft_strcmp(args[i], "<<") == 0 && args[i + 1])
		{
			if (!ft_strcmp(args[i + 1], last_red->next->text))
				last_red_index = i;
			handle_heredoc(&args, &i, mini);
		}
		else
			i++;
	}
	if (last_red_index != -1)
	{
		i = 0;
		while (args[i])
		{
			if ((!ft_strcmp(args[i], "<") || !ft_strcmp(args[i], ">") || !ft_strcmp(args[i], ">>")) && i != last_red_index)
			{
				move_left_args(args, i, last_red->next->text);
				move_left_args(args, i, last_red->next->text);
			}
			else
				i++;
		}
		last_red_index = check_dup(args, last_red->next->text);
		i = last_red_index + 1;
		if (!ft_strcmp(args[last_red_index], "<"))
			handle_output(&args, &i, mini);
	}
}

void handle_redirection(char **args, t_mini *mini,  t_token *token)
{
	t_token *last_redirect;
	
	// count_redirections(token);
	last_redirect = ft_tokenlast_redirect(token);
	if(mini->input_count > 1 || mini->output_count > 1 || mini->append_count > 1)
		handle_mult_redirections(args, mini, last_redirect);
	else
		handle_single_redirection(args, mini, last_redirect);
}
int	check_file2(char **args, t_token **token, t_mini *mini)
{
	args[0] = ft_strdup((*token)->text);
	handle_redirection(args, mini, *token);
	// int i = 0;
	// while (args[i])
	// {
	// 	ft_printf("args[%d]: %s\n", i, args[i]);
	// 	i++;
	// }
	if (execve((*token)->text, args, mini->penv) == -1)
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_CMD),
			(*token)->text);
		return (0);
	}
	return (1);
}

