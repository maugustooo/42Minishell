/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:20:52 by maugusto          #+#    #+#             */
/*   Updated: 2024/07/31 13:58:25 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_mini mini;
	t_token *token;

	token = NULL;
	ft_memset(&mini, 0, sizeof(t_mini));
	parse(&mini, &token);
}