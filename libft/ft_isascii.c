/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:16:34 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 10:41:32 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @file ft_isascii.c
 * @brief Checks if characther is in the ascii table
 */

#include "libft.h"

/**
 * @brief Verifies if c is in ascii table
 * 
 * @param c Character
 * @return int 1 if he is on ascii table | 0 if not
 */
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/**@}*/