/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 10:23:59 by maugusto          #+#    #+#             */
/*   Updated: 2024/07/30 15:19:27 by gude-jes         ###   ########.fr       */
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
	char			*line;
	int				type;
	struct s_token	*next;
} t_token;


typedef struct s_mini
{
	char	*line;
} t_mini;


//--------------Parser------------//

void	*get_line(t_mini *mini);
t_token	**get_tokens(t_mini *mini);

//------------Executor-----------//

void	handle_cd(t_token *arg, char *prev_dir);
void    handle_exit(char *prev_dir);

#endif