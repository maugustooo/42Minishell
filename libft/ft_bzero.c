/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:05:36 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 10:37:37 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_bzero.c
 * @brief Fill an array with null '\0'
*/

#include "libft.h"

/**
 * @brief Fill an array with null's
 * 
 * @param str Array
 * @param n number of elements
 */
void	ft_bzero(void *str, size_t n)
{
	size_t			i;
	unsigned char	*s;

	s = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		s[i] = '\0';
		i++;
	}
}

/**@}*/