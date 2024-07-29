/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:20:52 by maugusto          #+#    #+#             */
/*   Updated: 2024/07/29 14:33:54 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_mini mini;
	
	get_line(&mini);
}