/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 10:23:59 by maugusto          #+#    #+#             */
/*   Updated: 2024/07/31 12:34:16 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <sys/stat.h>
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

#define HOME "/home/$USER"

typedef struct s_token
{
	char			*text;
	int				type;
	struct s_token	*next;
} t_token;


typedef struct s_mini
{
	char	*line;
} t_mini;

//--------------Utils-------------//

t_token	*ft_tokenlast(t_token *token);
void	ft_tokenadd_back(t_token **token, t_token *new);
t_token	*ft_newnode(int type, char *text);
void	ft_tokenclear(t_token **token);
void	free_split(char **split);
//--------------Parser------------//

void get_line(t_mini *mini, t_token	**token);
void get_tokens(t_token	**token, char ***splited);

//------------Executor-----------//

void	handle_cd(t_token *arg, char **prev_dir);
void    handle_exit(char **prev_dir);
void	handle_echo(char *flag, t_token *next);
void	handle_env(t_token *next);
void	handle_pwd();
void    executor(t_token **token);

#endif