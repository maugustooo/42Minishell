/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:18:30 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 12:21:01 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_toupper.c
 * @brief Transform a letter to uppercase
*/

#include "libft.h"

/**
 * @brief If c character if lowercase transform it into uppercase
 * 
 * @param c Character to be transformed
 * @return int C character transformed or not
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

/**@}*/