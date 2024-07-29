/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 08:44:35 by gude-jes          #+#    #+#             */
/*   Updated: 2024/04/23 10:20:54 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_printf_utils.c
 * @brief Utils for ft_printf
*/

#include "../libft.h"

/**
 * @brief Print a string without return
 * 
 * @param str String to be printed
*/
void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

/**
 * @brief Print a string
 * 
 * @param str String to be printed
 * @return int Length of string
*/
int	ft_printstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

/**
 * @brief Prints a number
 * 
 * @param n Number to be printed
 * @return int length of number converted to string
*/
int	ft_printnbr(int n)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_itoa(n);
	len = ft_printstr(num);
	free(num);
	return (len);
}

/**
 * @brief Prints %
 * 
 * @return int 1 due to length of %
*/
int	ft_printpercent(void)
{
	write(1, "%", 1);
	return (1);
}
