/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:11:25 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/31 22:04:05 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_token *token, t_token *last)
{
	char	*line;
	int		fd;
	char	*delimiter;

	delimiter = token->next->text;
	fd = open(last->text, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}
void output2(t_token *token)
{
    int after_file;
    int first_arg;
	
	after_file = 0;
	first_arg = 1;
    while (token && token->type != PIPE)
    {
        if (token->type == FILE)
            after_file = 1;
        if (token->type != ARG)
        {
            token = token->next;
            continue;
        }
        if (!first_arg)
            ft_printf_fd(STDOUT_FILENO, " ");
        ft_printf_fd(STDOUT_FILENO, "%s", token->text);
        first_arg = 0;
        token = token->next;
    }
    ft_printf_fd(STDOUT_FILENO, "\n");
}

void	check_input2(t_token *token, t_mini *mini)
{
	mini->echo_flag = true;
	output2(token);
	dup2(mini->saved_stdout, STDOUT_FILENO);
	close(mini->saved_stdout);
}

int	check_input(t_token *token, t_mini *mini)
{
	t_token	*temp;
	t_token	*file;
	int return_value;

	return_value = 0;
	temp = token;
	while (temp && temp->type != PIPE)
	{
		file = ft_finde_file(temp);
		if ((temp->type == OUTPUT || temp->type == APPEND)
			&& !ft_find_c('"', temp->text) && !ft_find_c('\'', temp->text)
			&& mini->num_outs-- == 1)
			{
				check_input2(token, mini);
				return_value = 1;
			}
		if (temp->type == HERE && !ft_find_c('"', temp->text)
			&& !ft_find_c('\'', temp->text))
			heredoc(token, file);
		temp = temp->next;
	}
	return (return_value);
}

int	check_valid_n_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] && str[i] == 'n')
			i++;
		return (str[i] == '\0');
	}
	return (0);
}

int	handle_n_flag(t_token **next)
{
	int	n_flag;

	n_flag = 0;
	while ((*next) && (ft_strncmp((*next)->text, "-n", 2) == 0)
		&& check_valid_n_flag((*next)->text))
	{
		n_flag++;
		(*next) = (*next)->next;
	}
	return (n_flag);
}
