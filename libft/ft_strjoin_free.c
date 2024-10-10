/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:20:30 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/10 12:23:45 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup bonus Bonus
 * @{
 * @file ft_strjoin_free.c
 * @brief Creates a new string, joins the 2 strings passed as parameter and
 * frees one of the strings
*/

#include "libft.h"

/**
 * @brief String Join with free
 * 
 * @param s1 String 1
 * @param s2 String 2
 * @param to_free Num to free
 * @return char* Returns the joined string
*/
char	*ft_strjoin_free(char *s1, char *s2, int to_free)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	if (to_free == 1 || to_free == 3)
		free(s1);
	if (to_free == 2 || to_free == 3)
		free(s2);
	return (new_str);
}

/**@}*/