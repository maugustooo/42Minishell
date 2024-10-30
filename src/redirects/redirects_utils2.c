/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:12:20 by marvin            #+#    #+#             */
/*   Updated: 2024/10/30 11:12:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void handle_permission_error(char ***args, int *i, enum e_error error)
{
    ft_printf_fd(STDERR_FILENO, error_msg(error), (*args)[*i + 1]);
    move_left((*args), *i);
    move_left((*args), *i);
}
