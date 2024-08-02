/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 08:44:35 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/02 11:55:21 by maugusto         ###   ########.fr       */
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
 * @brief Print a string
 * 
 * @param str String to be printed
 * @return int Length of string
*/
int	ft_printstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	while (str[i])
	{
		write(fd, &str[i], 1);
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
int	ft_printnbr_fd(int n, int fd)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_itoa(n);
	len = ft_printstr_fd(num, fd);
	free(num);
	return (len);
}

/**
 * @brief Prints %
 * 
 * @return int 1 due to length of %
*/
int	ft_printpercent_fd(int fd)
{
	write(fd, "%", 1);
	return (1);
}
