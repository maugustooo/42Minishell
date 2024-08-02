/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:23:10 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/02 12:40:54 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_printf.c
 * @brief Main file of ft_printf
*/

#include "../libft.h"

/**
 * @brief Checker of character after %
 * 
 * @param str String
 * @param i Position of string
 * @param ap Variatic Arguments
 * @return int Length of printable
*/
static int	ft_check(int fd, const char *str, int i, va_list ap)
{
	if (str[i] == 'c')
		return (ft_printchar_fd(va_arg(ap, int), fd));
	else if (str[i] == 's')
		return (ft_printstr_fd(va_arg(ap, char *), fd));
	else if (str[i] == 'p')
		return (ft_putptr_fd( va_arg(ap, void *), fd));
	else if (str[i] == 'd' || str[i] == 'i')
		return (ft_printnbr_fd( va_arg(ap, int), fd));
	else if (str[i] == 'u')
		return (ft_uitoa_fd( va_arg(ap, unsigned int), fd));
	else if (str[i] == 'x' || str[i] == 'X')
		return (ft_putnbrhex_fd( va_arg(ap, int), str[i], fd));
	else if (str[i] == '%')
		return (ft_printpercent_fd(fd));
	return (0);
}

/**
 * @brief Main function of ft_printf
 * 
 * @param str First part of the string
 * @param ... Variatic arguments
 * @return int Length of printable string
*/
int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	ap;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (!str || *str == '\0')
		return (0);
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			while (!ft_strchr("cspdiuxX%", str[i]))
				i++;
			ret += ft_check(fd, str, i, ap);
		}
		else
			ret += ft_printchar_fd(str[i], fd);
		i++;
	}
	va_end(ap);
	return (ret);
}

/**@}*/