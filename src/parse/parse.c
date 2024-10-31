/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 08:50:25 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/16 10:59:29 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	

static int	have_pipe(t_token *token, t_mini *mini)
{
	int	flag;

	mini->after_pipe = true;
	flag = 0;
	while (token)
	{
		if (token->type == PIPE)
		{
			if (!token->next)
				mini->after_pipe = false;
			mini->num_pipes++;
			flag = 1;
		}
		token = token ->next;
	}
	return (flag);
}

static int	check_no_file(t_token *token, t_mini *mini)
{
	t_token	*temp;
	int		input;

	input = 0;
	temp = token;
	while (temp)
	{
		if (temp->type == INPUT || ft_find_c('<', temp->text))
			input = 1;
		if (temp->type == APPEND || temp->type == OUTPUT)
			input = 0;
		if (temp->type == NFILE && (input || (ft_find_c('<', temp->text))))
		{
			if (!mini->pipe)
				ft_printf_fd(STDERR_FILENO, error_msg(ERROR_NFILE), temp->text);
			if (ft_find_c('<', temp->text) && temp->next
				&& temp->next->type != FILE)
				mini->return_code = 2;
			return (0);
		}
		if (!check_perms(temp, input, mini))
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	syntax_errors(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if ((tmp->type == OUTPUT || tmp->type == INPUT || tmp->type == APPEND
				|| tmp->type == HERE))
		{
			if (tmp->next && return_redirect(tmp->next))
				return (ft_printf_fd(STDERR_FILENO, error_msg(ERROR_SNTAX_RED),
						tmp->next->text), 0);
			else if (!tmp->next && (tmp->text[0] == '<' || tmp->text[0] == '>'
					|| (tmp->text[0] == '>' && tmp->text[1] == '>')))
				return (ft_printf_fd(STDERR_FILENO, error_msg(ERROR_ECHO_RED),
						tmp->text), 0);
		}
		if (tmp->type == PIPE && tmp->next && tmp->next->type == PIPE)
			return (ft_printf_fd(STDERR_FILENO, error_msg(ERROR_SNTAX_RED),
					tmp->next->text), 0);
		if (tmp->type == CMD && (ft_strcmp(tmp->text, "|") == 0 || next(tmp)))
			return (ft_printf_fd(STDERR_FILENO, error_msg(ERROR_SNTAX_RED),
					tmp->text), 0);
		tmp = tmp->next;
	}
	return (1);
}

void	check_red_cmd(t_token **token)
{
	int	fd;

	fd = 0;
	while (*token)
	{
		if ((*token)->type == CMD && (ft_strcmp((*token)->text, ">") == 0
				|| ft_strcmp((*token)->text, ">>") == 0) && (*token)->next)
		{
			if (ft_strcmp((*token)->text, ">") == 0)
				fd = open((*token)->next->text, 577, 0644);
			else if (ft_strcmp((*token)->text, ">>") == 0)
				fd = open((*token)->next->text, 577, 0644);
			if (fd < 0)
				return ;
			remove_node(token);
			remove_node(token);
			continue ;
		}
		if (*token && (*token)->next)
			(*token) = (*token)->next;
		else
			break ;
	}
	while (*token && (*token)->prev)
		(*token) = (*token)->prev;
}

/**
 * @brief Will parse creating the tokens and checking commands
 * 
 * @param mini The struct of the minishell
 * @param token the list of tokens
 * @param splited the tokens splited
 * @return 0 if ther's an error and 1 if not 
 */
int	parse(t_mini *mini, t_token	**token, char **envp)
{
	if (!mini->penv)
		dup_envp(mini, envp);
	get_tokens(token, mini);
	if (!syntax_errors(*token))
		return (0);
	if (ft_strncmp((*mini->splited), "echo", 4) == 0 && (*token)->next)
		if (ft_strncmp((*token)->next->text, "-n", 2) == 0)
			mini->echo_flag = true;
	getcwd(mini->curr_dir, sizeof(mini->curr_dir));
	if (have_pipe(*token, mini) || mini->final_pipe)
		mini->pipe = true;
	if (!check_no_file(*token, mini) && !mini->pipe)
	{
		if (mini->return_code != 2)
			mini->return_code = 1;
		create_outfiles(*token);
		return (0);
	}
	remove_dup_files(token);
	check_red_cmd(token);
	if (!token || !*token)
		return (0);
	mini->saved_stdout = dup(STDOUT_FILENO);
	if (mini->after_pipe == false)
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_UNCLOSED_PIPE));
	return (1);
}
