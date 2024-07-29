/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:06:41 by gude-jes          #+#    #+#             */
/*   Updated: 2024/04/23 10:20:59 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_putchar.c
 * @brief Prints a character 
*/

#include "../libft.h"

/**
 * @brief Print a character 
 * 
 * @param c Character to be printed
 * @return int Length of character - 1
*/
int	ft_putchar(char c)
{
	write (1, &c, 1);
	return (1);
}

/**@}*/