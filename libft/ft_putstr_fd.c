/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:17:30 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 11:21:27 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_putstr_fd.c
 * @brief Outputs the string ’s’ to the given file descriptor.
*/

#include "libft.h"

/**
 * @brief Writes the s string to the file descriptor
 * 
 * @param s String
 * @param fd File descriptor
 */
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write (fd, s, ft_strlen(s));
}

/**@}*/