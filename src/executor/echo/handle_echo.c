/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:04:24 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/31 22:01:41 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if(parse_echo(temp, mini) == 1)
		return ;
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
