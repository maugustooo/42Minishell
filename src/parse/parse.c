/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 08:50:25 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/02 09:31:53 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_arg_export(t_token *token, t_mini *mini)
{
	char	*value;
	char	**key;
	char	*check;

	key = NULL;
	while(token->next)
	{
		check = ft_strchr(token->next->text, '=');
		key = ft_split(token->next->text, '=');
		if(check)
			check++;
		if (token->next)
		{
			if(check != NULL)
				value = check;
			if(!ft_str_isalpha(key[0]) && !ft_strchr(key[0], '_'))
			{
				ft_printf(Error_Msg(ERROR_EXPORT), token->next->text);
				mini->return_code = 1;
				mini->exported = true;
				free_key(key);
				return ;
			}
		}
		free_key(key);
		token = token->next;
	}
}	

static int have_pipe(t_token *token)
{
	int flag;

	flag = 0;
	while (token)
	{
		if(token->type == PIPE || ft_find_c('|', token->text))
			flag = 1;
		token = token ->next;
	}
	return(flag);
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
	if(ft_strcmp((*mini->splited), "export") == 0 && (*token)->next)
		check_arg_export(*token, mini);
	if(have_pipe(*token) || mini->final_pipe)
		mini->pipe = true;
	return(1);
}
