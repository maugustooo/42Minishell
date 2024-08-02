/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:06:41 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/02 11:16:14 by maugusto         ###   ########.fr       */
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
int	ft_printchar_fd(char c, int fd)
{
	write (fd, &c, 1);
	return (1);
}

/**@}*/