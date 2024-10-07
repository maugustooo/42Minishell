/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum_under.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:39:43 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/07 14:48:03 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup bonus Bonus
 * @{
 * @file ft_isalnum_under.c
 * @brief Check if character is alphanumeric or underscore.
*/

#include "libft.h"

/**
 * @brief Checks if character is alphanumeric or underscore
 * 
 * @param c Character to check
 * @return int 1 if true | 0 if flase
*/
int	ft_isalnum_under(int c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

/**@}*/