/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:18:28 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 12:19:15 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_tolower.c
 * @brief Transform a letter to lowercase
*/

#include "libft.h"

/**
 * @brief If c character if uppercase transform it into lowercase
 * 
 * @param c Character to be transformed
 * @return int C charater transformed or not
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

/**@}*/