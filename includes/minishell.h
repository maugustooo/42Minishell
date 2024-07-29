/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 10:23:59 by maugusto          #+#    #+#             */
/*   Updated: 2024/07/29 15:45:18 by maugusto         ###   ########.fr       */
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



void *get_line(t_mini *mini);
t_token **get_tokens(t_mini *mini);

#endif