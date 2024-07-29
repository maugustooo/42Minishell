/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:18:07 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 11:45:52 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_strjoin.c
 * @brief Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’.
*/

#include "libft.h"

/**
 * @brief Concatenates s1 and s2 and returns a new string
 * 
 * @param s1 First string
 * @param s2 Second string
 * @return char* New string
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	int		i;
	int		j;
	char	*newstring;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	newstring = (char *)malloc(sizeof(char) * (size + 1));
	if (!newstring)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		newstring[i] = s1[i];
	while (s2[++j])
		newstring[i + j] = s2[j];
	newstring[i + j] = '\0';
	return (newstring);
}

/**@}*/