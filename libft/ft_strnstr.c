/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:18:19 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 12:09:24 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_strnstr.c
 * @brief Locate a substring in a string
*/

#include "libft.h"

/**
 * @brief Locates little inside big based on len
 * 
 * @param big String to be searched
 * @param little String to search
 * @param len Size to search
 * @return char* If little doesn't exist returns big. Othewise returns little
 *  or 0 if not found
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!little[0])
		return ((char *)big);
	j = 0;
	while (j < len && big[j])
	{
		i = 0;
		while (j < len && little[i] && big[j] && little[i] == big[j])
		{
			++i;
			++j;
		}
		if (!little[i])
			return ((char *)&big[j - i]);
		j = j - i + 1;
	}
	return (0);
}

/**@}*/