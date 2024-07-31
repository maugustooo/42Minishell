/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:35:32 by maugusto          #+#    #+#             */
/*   Updated: 2024/07/31 18:19:20 by maugusto         ###   ########.fr       */
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
/**
 * @brief check is a comand and if echo has the flag -n
 * 
 * @param cmd the command
 * @param token the node with the informations
 * @param mini the struct
 * @return 1 if is a command 0 if is not
 */
int check(char	*cmd, t_token *token, t_mini *mini)
{
	t_token *current;

	current = token;
	if(ft_strncmp(cmd, "echo", 4) == 0 && token->next)
		if(ft_strncmp(token->next->text, "-n", 2) == 0)
			mini->echo_flag = true;
	if(ft_strncmp(cmd, "cd", 2) == 0|| ft_strncmp(cmd, "echo", 4) == 0
		|| ft_strncmp(cmd, "pwd", 3) == 0|| ft_strncmp(cmd, "export", 6) == 0
		|| ft_strncmp(cmd, "unset", 5) == 0|| ft_strncmp(cmd, "exit", 4) == 0
		|| ft_strncmp(cmd, "exit", 4) == 0 || ft_strncmp(cmd, "env", 4) == 0)
			return(1);
	return(0);
}
/**
 * @brief Will parse creating the tokens and checking commands
 * 
 * @param mini The struct of the minishell
 * @param token the list of tokens
 * @param splited the tokens splited
 * @return 0 if ther's an error and 1 if not 
 */
int parse(t_mini *mini, t_token	**token, char ***splited)
{
		get_tokens(token, splited);
		if(!check(**splited, *token, mini))
			return(ft_printf(Error_Msg(ERROR_CMD), **splited), 0);
	return(1);
}
