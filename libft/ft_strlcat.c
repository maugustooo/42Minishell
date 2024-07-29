/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:18:09 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 11:49:45 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_strlcat.c
 * @brief Function appends the NUL-terminated string
 *  src to the end of dst.  It will append at most size - strlen(dst) - 1 bytes,
 *  NUL-terminating the result.
*/

#include "libft.h"

/**
 * @brief Apends src to dest by n bytess
 * 
 * @param dst Destination string
 * @param src Source string
 * @param size Bytes to append
 * @return size_t Returns the lenght of src + dest
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_length;
	size_t	src_length;

	src_length = ft_strlen(src);
	if (!dst && size == 0)
		return (src_length);
	dest_length = ft_strlen(dst);
	j = dest_length;
	i = 0;
	if (dest_length < size - 1 && size > 0)
	{
		while (src[i] && dest_length + i < size - 1)
		{
			dst[j] = src[i];
			j++;
			i++;
		}
		dst[j] = 0;
	}
	if (dest_length >= size)
		dest_length = size;
	return (dest_length + src_length);
}

/**@}*/