/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:19:20 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/08 09:32:23 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_strstr.c
 * @brief 
*/

#include "libft.h"

/**
 * @brief Check if a substring exists on a string
 * 
 * @param str Main String
 * @param to_find String to find
 * @return char* Pointer to the first characters of to_find in str.
 * Can return NULL if to_find is not found in str. If to find is empty
 * the str will be returned
*/
char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (to_find[j] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		while (str[i + j] == to_find[j] && str[i + j] != '\0')
			j++;
		if (to_find[j] == '\0')
			return (str + i);
		i++;
		j = 0;
	}
	return (0);
}

/**@} */