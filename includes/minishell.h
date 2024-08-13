/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 10:23:59 by maugusto          #+#    #+#             */
/*   Updated: 2024/08/13 10:46:47 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
#include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define CMD 1
# define ARG 2
# define INPUT 3
# define OUTPUT 4
# define DELIMITER 5
# define APPEND 6
# define PIPE 7

# define MAX_PATH_LEN 4096

# define HOME "/home/$USER"

typedef enum e_error
{
	ERROR_CMD,
	ERROR_CD,
	ERROR_EXPORT,
	ERROR_ENV
}	t_error;

// const char *Error_Msg[] =
// {
//     [ERROR_CMD] = "%s: command not found",
//     /* etc. */  
// };

static inline const char *Error_Msg(enum e_error i)
{
    static const char *strings[] = { "%s: command not found\n",
	"minishell: cd: %s: No such file or directory",
	"minishell: export: `%s': not a valid identifier\n",
	"banana", /* continue for rest of values */ };
    return strings[i];
}

typedef struct s_token
{
	char			*text;
	int				type;
	struct s_token	*next;
} t_token;



typedef struct s_mini
{
	char	*line;
	char	**penv;
	char	*prev_dir;
	char	**splited;
	bool	echo_flag;
} t_mini;

//--------------Utils-------------//

t_token	*ft_tokenlast(t_token *token);
void	ft_tokenadd_back(t_token **token, t_token *new);
t_token	*ft_newnode(int type, char *text);
void	ft_tokenclear(t_token **token);
void	freethem(t_token **token, t_mini *mini);
void	free_penv(t_mini *mini);
void	dup_env(t_mini *mini, char **envp);
//--------------Parser------------//

int		parse(t_mini *mini, t_token	**token, char **envp);
void	get_tokens(t_token	**token, t_mini *mini);
void	handle_sigint(int sig);
void	handle_eof(t_token **token, t_mini *mini);

//------------Executor-----------//

void	handle_cd(t_token *arg, t_mini *mini);
void    handle_exit(t_token **token, t_mini *mini);
void	handle_echo(t_token *next, t_mini *mini);
void	handle_env(t_mini *mini, t_token *next);
void	handle_pwd();
void	set_export(t_mini *mini, t_token *token);
void	handle_export(t_mini *mini, t_token *token);
void	handle_unset(t_token *token, t_mini *mini);
void    executor(t_token **token, t_mini *mini);

#endif