/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:17:15 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 11:05:56 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_memcpy.c
 * @brief Copy N bytes of source to destination
*/

#include "libft.h"

/**
 * @brief Copy n bytes of content of src to dest 
 * 
 * @param dest Destination
 * @param src Source
 * @param n Number of bytes
 * @return void* Pointer to dest
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!n || (!d && !s))
		return (dest);
	while (n--)
		*d++ = *s++;
	return (dest);
}

/**@}*/