/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:17:23 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 11:12:50 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_putchar_fd.c
 * @brief Outputs the character ’c’ to the given file descriptor.
*/

#include "libft.h"

/**
 * @brief Writes the character c to the fd
 * 
 * @param c Character
 * @param fd File Descriptor
 */
void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

/**@}*/