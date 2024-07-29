/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:17:25 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 11:19:06 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_putendl_fd.c
 * @brief Outputs the string ’s’ to the given file descriptor
followed by a newline.
*/

#include "libft.h"

/**
 * @brief Writes the string s onto the file descriptor then writes a new line
 * 
 * @param s String to write
 * @param fd File Descriptor
 */
void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	write (fd, s, ft_strlen(s));
	write (fd, "\n", 1);
}

/**@}*/