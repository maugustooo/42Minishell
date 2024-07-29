/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:16:21 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 10:39:32 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_isalnum.c
 * @brief Check if characther is alphanumeric
 */

#include "libft.h"

/**
 * @brief Verifies if c is alphanumeric
 * 
 * @param c Character
 * @return int 1 if charater is alphanumeric | 0 if not
 */
int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

/**@}*/