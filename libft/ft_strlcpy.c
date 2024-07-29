/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:23:18 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 11:53:19 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_strlcpy.c
 * @brief Function copies up to size - 1 characters from the
 *  NUL-terminated string src to dst, NUL-terminating the result.
*/

#include "libft.h"

/**
 * @brief Copies n size characters from src to dest
 * 
 * @param dst Destination string
 * @param src Source string
 * @param n Number of characters
 * @return size_t Length of the source string
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	size;

	size = ft_strlen(src);
	i = 0;
	if (!dst || !src)
		return (0);
	if (n <= 0)
		return (size);
	while ((src[i]) && (i < (n - 1)))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (size);
}

/**@}*/