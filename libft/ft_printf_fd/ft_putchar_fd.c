/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:40:13 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/07 14:51:33 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief Writes the character c to the fd
 * 
 * @param c Character
 * @param fd File Descriptor
 */
int	ft_printchar_fd(char c, int fd)
{
	write (fd, &c, 1);
	return (1);
}
