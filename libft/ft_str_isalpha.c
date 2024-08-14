/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isalpha.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:16:23 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/14 10:39:42 by gude-jes         ###   ########.fr       */
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
	int i;
	
	i = -1;
	while (str[++i])
		if (!ft_isalpha(str[i]))
			return (0);
	return (1);
}

/**@}*/