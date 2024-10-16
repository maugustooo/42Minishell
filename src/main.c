/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:38:40 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/16 12:01:06 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

char	*error_msg(enum e_error i)
{
	char	*strings[17];

	strings[0] = "%s: command not found\n";
	strings[1] = "miniShell: cd: %s: No such file or directory\n";
	strings[2] = "miniShell: export: `%s': not a valid identifier\n";
	strings[3] = "Syntax error near '%s'\n";
	strings[4] = "ARG ECHO ERROR\n";
	strings[5] = "ERROR NO ENV\n";
	strings[6] = "miniShell: %s: too many arguments\n";
	strings[7] = "miniShell: %s: numeric argument required\n";
	strings[8] = "miniShell: %s: Is a directory\n";
	strings[9] = "miniShell: %s: Permission denied\n";
	strings[10] = "env: Options/Arguments not allowed by subject\n";
	strings[11] = "miniShell: cd: %s: Not a directory\n";
	strings[12] = "miniShell: %s: No such file or directory\n";
	strings[13] = "miniShell: exit: %s: numeric argument required\n";
	strings[14] = "syntax error near unexpected token `newline'\n";
	strings[15] = "syntax error near unexpected token `%s'\n";
	strings[16] = "NO unclosed pipes are allowed\n";
	return (strings[i]);
}

/**
 * @brief on a loop, will handle the readlines, parse, do the executor and
 * free everything
 * 
 * @param mini the struct
 * @param token the list of tokens
 */
void	minishell(t_mini *mini, t_token	**token, char **envp)
{
	while (1)
	{
		ft_signals();
		mini->rl = readline("miniShell: ");
		if (!mini->rl)
			handle_eof(token, mini);
		mini->line = mini->rl;
		if (mini->line[0])
			split_to_tokens(mini->line, mini);
		if (!mini->splited || !mini->splited[0])
		{
			freethem(token, mini);
			continue ;
		}
		add_history(mini->line);
		if (!parse(mini, token, envp))
		{
			free_things(mini);
			freethem(token, mini);
			continue ;
		}
		executor(token, mini);
		freethem(token, mini);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	t_token	*token;

	(void)argc;
	(void)argv;
	token = NULL;
	ft_memset(&mini, 0, sizeof(t_mini));
	minishell(&mini, &token, envp);
}
