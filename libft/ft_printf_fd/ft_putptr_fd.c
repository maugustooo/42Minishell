/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:35:41 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/02 11:58:10 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_putptr.c
 * @brief Print a memory space through a hexadecimal number
*/

#include "../libft.h"

/**
 * @brief Prints memory space as a hexadecimal number
 * 
 * @param nbr Number
 * @param c Base
 * @return int Length of number
*/
int	putptrhex_fd(unsigned long nbr, const char c, int fd)
{
	char	*base;
	int		result;

	result = 0;
	if (c == 'x')
		base = "0123456789abcdef";
	else if (c == 'X')
		base = "0123456789ABCDEF";
	if (nbr >= 16)
	{
		result += putptrhex_fd((nbr / 16), c, fd);
		result += putptrhex_fd((nbr % 16), c, fd);
	}
	else
	{
		result += write(fd, &base[nbr], 1);
	}
	return (result);
}

/**
 * @brief Handles edge cases and prints the start of the memory space
 * 
 * @param nbr Pointer to be printed
 * @return int Length of the hexadecimal
*/
int	ft_putptr_fd(void *nbr, int fd)
{
	int				result;
	unsigned long	n;

	n = (unsigned long)nbr;
	result = 0;
	if (!n)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	result += ft_printstr_fd("0x", fd);
	if (n == 0)
		result += ft_printchar_fd(0, fd);
	else
		result += putptrhex_fd(n, 'x', fd);
	return (result);
}

/**@}*/