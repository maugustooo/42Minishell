/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 08:50:25 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/25 15:25:57 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	

static int have_pipe(t_token *token, t_mini *mini)
{
	int flag;

	flag = 0;
	while (token)
	{
		if(token->type == PIPE)
		{
			mini->num_pipes++;
			flag = 1; 
		}
		token = token ->next;
	}
	return(flag);
}

static int check_no_file(t_token *token)
{
	t_token *temp;

	temp = token;
	while (temp)
	{
		if(temp->type == NOT_FILE)
		{
			ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_NFILE), temp->text);
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}
/**
 * @brief Will parse creating the tokens and checking commands
 * 
 * @param mini The struct of the minishell
 * @param token the list of tokens
 * @param splited the tokens splited
 * @return 0 if ther's an error and 1 if not 
 */
int parse(t_mini *mini, t_token	**token, char **envp)
{
	get_tokens(token, mini);
	if(!mini->penv)
		dup_envp(mini, envp);
	if(ft_strncmp((*mini->splited), "echo", 4) == 0 && (*token)->next)
		if(ft_strncmp((*token)->next->text, "-n", 2) == 0)
			mini->echo_flag = true;
	getcwd(mini->curr_dir, sizeof(mini->curr_dir));
	if(ft_strcmp((*mini->splited), "export") == 0 && (*token)->next)
		check_arg_export((*token)->next, mini);
	if(have_pipe(*token, mini) || mini->final_pipe)
		mini->pipe = true;
	if(!check_no_file(*token))
	{
		mini->return_code = 1;
		return(0);
	}
	return(1);
}
