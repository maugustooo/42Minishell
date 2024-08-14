/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:35:32 by maugusto          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/14 13:56:55 by maugusto         ###   ########.fr       */
=======
/*   Updated: 2024/08/14 10:43:50 by gude-jes         ###   ########.fr       */
>>>>>>> gude-jes
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	check_arg_export(t_token *token)
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
				return ;
			}
		}
		//TODO: Check this
		free(key[0]);
		free(key[1]);
		free(key);
		token = token->next;
	}
}

// static void handle_pipe(t_token *token)
// {
// 	if(token->next->type == ARG)
// 		ft_strlcat(token->text, token->next->text, ft_strlen(token->next->text));
	
// }
// static int have_pipe(t_token *token)
// {
// 	int flag;

// 	flag = 0;
// 	while (token)
// 	{
// 		if(token->type == PIPE)
// 			flag = 1;
// 		token = token ->next;
// 	}
// 	return(flag);
// }
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
		dup_env(mini, envp);
	if(ft_strncmp((*mini->splited), "echo", 4) == 0 && (*token)->next)
		if(ft_strncmp((*token)->next->text, "-n", 2) == 0)
			mini->echo_flag = true;
	if(ft_strcmp((*mini->splited), "export") == 0 && (*token)->next)
		check_arg_export(*token);
	// if(have_pipe(*token))
	// 	handle_pipe(*token);
	return(1);
}
