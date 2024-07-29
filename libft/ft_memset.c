/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:17:20 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 11:11:28 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_memset.c
 * @brief Set the n bytes of memory with a character
*/

#include "libft.h"

/**
 * @brief Sets n bytes of str memory with c
 * 
 * @param str Memory spac
 * @param c Character to set
 * @param n Number of bytes
 * @return void* Pointer to memory setted
 */
void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*s;

	s = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		s[i] = c;
		i++;
	}
	return (s);
}

/**@}*/