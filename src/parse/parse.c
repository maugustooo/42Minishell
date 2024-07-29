/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:35:32 by maugusto          #+#    #+#             */
/*   Updated: 2024/07/29 13:09:17 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *get_line(t_mini *mini)
{
	char *line;
	void(*mini);
	line = readline("What i'v done: ");
	ft_printf("%s", line);
}