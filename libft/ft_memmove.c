/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:17:18 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 11:08:08 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_memmove.c
 * @brief Moves n bytes of memory from source to destiny
*/

#include "libft.h"

/**
 * @brief Moves n bytes of memory from src to dest
 * 
 * @param dest Pointer to destiny
 * @param src Pointer to source
 * @param n Number of bytes
 * @return void* Pointer to dest
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (s < d)
		while (n--)
			d[n] = s[n];
	else
		ft_memcpy(d, s, n);
	return (dest);
}

/**@}*/