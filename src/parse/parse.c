/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:35:32 by maugusto          #+#    #+#             */
/*   Updated: 2024/08/12 16:40:01 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * @brief will handle the ctrl+C to display a new line
 * 
 * @param sig SIGINT
 */
void handle_sigint(int sig)
{
    (void)sig;
    rl_replace_line("", 0);
    rl_on_new_line();
    printf("\n"); 
    rl_redisplay();
}
/**
 * @brief Will handle the ctrl+D to exit
 * 
 */
void handle_eof(void)
{
    printf("exit\n");
    exit(0);
}

void	check_arg_export(t_token *token)
{
	char	*value;
	char	**key;
	char	*check;

	key = NULL;
	check = ft_strchr(token->next->text, '=');
	key = ft_split(token->next->text, '=');
	if(check)
		check++;
	if (token->next)
	{
		if(check != NULL)
			value = check;
		if(!ft_str_isalnum(key[0]) && !ft_strchr(key[0], '_'))
		{
			ft_printf(Error_Msg(ERROR_EXPORT), token->next->text);
			return ;
		}
	}
	//TODO: Check this
	free(key[0]);
	free(key[1]);
	free(key);
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
		dup_env(mini, envp);
	if(ft_strncmp((*mini->splited), "echo", 4) == 0 && (*token)->next)
		if(ft_strncmp((*token)->next->text, "-n", 2) == 0)
			mini->echo_flag = true;
	if(ft_strcmp((*mini->splited), "export") == 0 && (*token)->next)
		check_arg_export(*token);
	return(1);
}
