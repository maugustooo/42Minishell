/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrhex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:47 by gude-jes          #+#    #+#             */
/*   Updated: 2024/04/26 11:22:16 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_putnbrhex.c
 * @brief Functions to print a hexadecimal 
*/

#include "../libft.h"

/**
 * @brief Get num length
 * 
 * @param num Number to get length
 * @return int Length of number
*/
int	ft_hex_len(unsigned	int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

/**
 * @brief Prints a number in hexadecimal base
 * 
 * @param num Number to be printed
 * @param c Uppercase or lowercase base
*/
void	ft_put_hex(unsigned int num, const char c)
{
	if (num >= 16)
	{
		ft_put_hex(num / 16, c);
		ft_put_hex(num % 16, c);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
		{
			if (c == 'x')
				ft_putchar_fd((num - 10 + 'a'), 1);
			if (c == 'X')
				ft_putchar_fd((num - 10 + 'A'), 1);
		}
	}
}

/**
 * @brief Checker of num
 * 
 * @param num Number to be checked
 * @param c Base
 * @return int Legth of number
*/
int	ft_putnbrhex(unsigned int num, const char c)
{
	if (num == 0)
		return (write(1, "0", 1));
	else
		ft_put_hex(num, c);
	return (ft_hex_len(num));
}

/**@}*/