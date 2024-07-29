/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:35:41 by gude-jes          #+#    #+#             */
/*   Updated: 2024/04/29 11:13:11 by gude-jes         ###   ########.fr       */
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
int	putptrhex(unsigned long nbr, const char c)
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
		result += putptrhex((nbr / 16), c);
		result += putptrhex((nbr % 16), c);
	}
	else
	{
		result += write(1, &base[nbr], 1);
	}
	return (result);
}

/**
 * @brief Handles edge cases and prints the start of the memory space
 * 
 * @param nbr Pointer to be printed
 * @return int Length of the hexadecimal
*/
int	ft_putptr(void *nbr)
{
	int				result;
	unsigned long	n;

	n = (unsigned long)nbr;
	result = 0;
	if (!n)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	result += ft_printstr("0x");
	if (n == 0)
		result += ft_putchar(0);
	else
		result += putptrhex(n, 'x');
	return (result);
}

/**@}*/