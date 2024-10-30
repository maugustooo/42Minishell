/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 08:52:34 by marvin            #+#    #+#             */
/*   Updated: 2024/10/30 08:52:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	handle_output_echo(t_mini *mini, t_token *token)
{
	int	fd_out;

	fd_out = 0;
	mini->redirect = 1;
    if (!token->next)
    {
        return ;
    }
	if (ft_strcmp(token->text, ">") == 0)
		fd_out = open(token->next->text, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(token->text, ">>") == 0)
		fd_out = open(token->next->text, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
		return ;
    if(fd_out != 0)
    {
	    dup2(fd_out, STDOUT_FILENO);
	    if (fd_out)
		    close(fd_out);
    }
}

int return_file(t_token *temp)
{
	return (((temp->type == FILE || temp->type == NFILE || temp->type == NO_PERM)
			&& (temp->prev->type == OUTPUT || temp->prev->type == APPEND)));
}

static void print_error(char *file, char *msg)
{
    char *prefix;
    char *suffix;
    char buffer[256];
    
    prefix = "miniShell: ";
    suffix = msg;
    strcpy(buffer, prefix);
    strcat(buffer, file);
    strcat(buffer, suffix);
    write(STDERR_FILENO, buffer, strlen(buffer));
}
static int	check_perms_echo(t_token *token)
{
	struct stat	path_stat;

	if (stat(token->text, &path_stat) == -1)
    {
		return (1);
    }
	if (S_ISREG(path_stat.st_mode))
	{
		if (access(token->text, W_OK) != 0)
        {
            print_error(token->text, ": Permission denied\n");
			return (1);
        }
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		print_error(token->text, " : Is a directory\n");
		return (1);
	}
	return (0);
}

int	parse_echo(t_token *token, t_mini *mini)
{
    t_token	*temp;

    temp = token;
    while (temp && temp->type != PIPE)
    {
        if(return_file(temp))
        {
            if (check_perms_echo(temp) == 1)
            {
                mini->return_code = 1;
                return (1);
            }
        }
        handle_output_echo(mini, temp);
        temp = temp->next;
    }
    return (0);
}
