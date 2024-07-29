/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:17:44 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 11:40:46 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_strdup.c
 * @brief function returns a pointer to a new string which is
 *  a duplicate of the string s. 
 * Memory for the new string is obtained with malloc(3),
 *  and can be freed with free(3).
*/

#include "libft.h"

/**
 * @brief Duplicates a string
 * 
 * @param src String to duplicate
 * @return char* Duplicated string
 */
char	*ft_strdup(const char *src)
{
	int		i;
	char	*dest;
	int		size;

	i = 0;
	size = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**@}*/