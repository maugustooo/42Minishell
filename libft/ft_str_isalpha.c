/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isalpha.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:16:23 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/07 14:45:00 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_str_isalpha.c
 * @brief Check if str is alphanumeric
*/

#include "libft.h"

/**
 * @brief Verifies if str is alphanumeric
 * 
 * @param str string
 * @return int 1 if alphanumeric | 0 if not
 */
int	ft_str_isalpha(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isalpha(str[i]))
			return (0);
	return (1);
}

/**@}*/