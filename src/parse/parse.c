/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 08:50:25 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/26 10:48:45 by maugusto         ###   ########.fr       */
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

t_token *ft_tokenpenultimate(t_token *head)
{
    t_token *current;
    
    if (head == NULL || head->next == NULL)
        return NULL;
    current = head;
    while (current->next && current->next->next)
        current = current->next;
    return (current);
}
// static void handle_pipes(t_token **token, t_mini *mini)
// {
//     char *before_pipe;
//     char *after_pipe;
// 	t_token *current_token;
// 	t_token *last;
//     t_token *penultimate;
// 	t_token *next_token;
	 
// 	current_token = (*token)->next;
// 	while (current_token)
// 	{
// 		if(ft_find_c('|', current_token->text))
// 		{
// 		 	before_pipe = ft_strndup(current_token->text, ft_strclen(current_token->text, '|'));
//             after_pipe = ft_strdup(current_token->text + ft_strclen(current_token->text, '|') + 1);
//             free(current_token->text);
// 			current_token->text = NULL;
// 			if (before_pipe[0])
//                 current_token->text = before_pipe;
//             else
//             {
//                 current_token->type = PIPE;
//                 current_token->text = ft_strdup("|");
//             }
//             if (after_pipe[0] != '\0')
//             {
//                 ft_tokenadd_back(token, ft_newnode(CMD, after_pipe));
// 				if (current_token->next && !ft_find_c('|', current_token->next->text))
//                     ft_tokenadd_back(token, ft_newnode(PIPE, "|"));
//             }
// 			else
//             	free(after_pipe);
// 			next_token = current_token->next;
//             current_token = next_token;
//         }
//         else
//             current_token = current_token->next;
// 	}
// 	last = ft_tokenlast(*token);
//     if (last && last->type == PIPE)
//         ft_tokendelone(last);
//     penultimate = ft_tokenpenultimate(*token);
//     if (penultimate && last->type == PIPE)
// 		penultimate->next = NULL;
// 	mini->pipe = true;
// }

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
		check_arg_export(*token);
	if(have_pipe(*token))
		mini->pipe = true;
	return(1);
}
