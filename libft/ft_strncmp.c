/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:18:16 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 11:57:03 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory 
 * @{
 * @file ft_strncmp.c
 * @brief Compares the only first n bytes of s1 and s2
*/

#include "libft.h"

/**
 * @brief Compare the first n bytes of s1 and s2
 * 
 * @param s1 First string
 * @param s2 Second string
 * @param n Bytes to compare
 * @return int Difference between s1 and s2
 */
int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] == s2[i]) && (i < n - 1) && s1[i] != '\0' && s1[i] != '\0')
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

/**@}*/