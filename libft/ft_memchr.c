/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:17:11 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 11:09:21 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_memchr.c
 * @brief The  memchr() function scans the initial n bytes of the memory area
 *  pointed to by s for the first instance of c.Both c and the bytes of the
 *  memory area pointed to by s are interpreted as unsigned char.
*/

#include "libft.h"

/**
 * @brief Checks the initial n bytes of the memory area pointed to by s
 *  for the first instance of c.
 * 
 * @param s Pointer to memory
 * @param c Character to stop
 * @param n Number of bytes
 * @return void* Pointer to memory
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s + i) == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}

/**@}*/