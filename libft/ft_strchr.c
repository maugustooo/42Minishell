/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:17:36 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 11:38:26 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_strchr.c
 * @brief Checks if a character exists in a string
*/

#include "libft.h"

/**
 * @brief Checks if c character exists in s string
 * 
 * @param s String
 * @param c Character to check
 * @return char* Pointer to first occurence of c in s
 */
char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char )c)
		s++;
	if (*s == (char )c || !c)
		return ((char *) s);
	return (NULL);
}

/**@}*/