/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:18:22 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 12:11:23 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_strrchr.c
 * @brief Function returns a pointer to the last occurrence
 *  of the character c in the string s.
*/

#include "libft.h"

/**
 * @brief Checks the last ocurrence of c in s
 * 
 * @param s String to check
 * @param c Character to find
 * @return char* Pointer to the ocurrence
 */
char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char )c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}

/**@}*/