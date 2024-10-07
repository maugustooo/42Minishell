/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:04:24 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/07 13:45:06 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	output2(t_token *token, t_mini *mini, int after_file, int fd)
{
	while (token)
	{
		if (token->type == FILE)
			after_file = 1;
		if (token->type != ARG)
		{
			token = token->next;
			continue ;
		}
		if ((token->type == ARG || token->type == FILE)
			&& ft_strcmp(token->text, "-n") != 0)
			ft_printf_fd(fd, "%s ", token->text);
		else if (!mini->echo_flag || after_file)
			ft_printf_fd(fd, "%s\n", token->text);
		else if (token->type == ARG && ft_strcmp(token->text, "-n") != 0)
			ft_printf_fd(fd, token->text);
		token = token->next;
	}
}

int	output(t_token *token, t_mini *mini, t_token *file_node, int type)
{
	int		fd;
	char	*file;
	int		after_file;

	after_file = 0;
	fd = 0;
	if (!file_node)
		return (2);
	if (file_node->type == ARG || file_node->type == FILE
		|| file_node->type == NOT_FILE)
		file = file_node->text;
	else
		ft_printf(error_msg(ERROR_ARG_ECHO));
	if (!check_file_perms(file_node))
		return (0);
	if (type == OUTPUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (type == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd)
		output2(token, mini, after_file, fd);
	else
		check_access(token->text);
	ft_printf_fd(fd, "\n");
	return (1);
}

int	print_echo2(t_token **next, t_mini *mini)
{
	int	redirect_status;

	redirect_status = check_redirect(next);
	if (redirect_status == 1)
		return (1);
	else if (redirect_status == 2)
	{
		mini->return_code = 1;
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_NFILE), (*next)->text);
		return (2);
	}
	return (0);
}

void	print_echo(t_token *next, t_mini *mini, int *first)
{
	int	n_flag;
	int	redirect_status;

	n_flag = handle_n_flag(&next);
	while (next && next->type != PIPE)
	{
		redirect_status = print_echo2(&next, mini);
		if (redirect_status == 1)
			continue ;
		else if (redirect_status == 2)
			break ;
		expander(&next, mini);
		if (*first)
			ft_printf(" ");
		ft_printf("%s", next->text);
		*first = 1;
		next = next->next;
	}
	if (n_flag == 0)
		ft_printf("\n");
}

void	handle_echo(t_token **token, t_mini *mini)
{
	int		first;
	t_token	*temp;
	int		check_input_return;

	check_input_return = 0;
	temp = *token;
	first = 0;
	if (temp->next)
	{
		temp = temp->next;
		check_input_return = check_input(temp, mini);
		if (check_input_return == 0)
			print_echo(temp, mini, &first);
		else if (check_input_return == 2)
			return ;
	}
	else
		ft_printf("\n");
	mini->return_code = 0;
}
