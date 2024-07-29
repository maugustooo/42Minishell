/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:16:38 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 10:42:35 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_isprint.c
 * @brief Checks if the characther is printable
*/

#include "libft.h"

/**
 * @brief Verifies if c in printable
 * 
 * @param c Character
 * @return int 1 if c is printable | 0 if not
 */
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

/**@}*/