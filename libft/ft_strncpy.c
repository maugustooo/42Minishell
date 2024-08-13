/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:06:33 by maugusto          #+#    #+#             */
/*   Updated: 2024/08/13 12:06:34 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies n size characters from src to dest
 * 
 * @param dst Destination string
 * @param src Source string
 * @param n Number of characters
 * @return size_t Length of the source string
 */
void	ft_strncpy(char *dst, const char *src, int n)
{
	int	i;

	i = 0;
	if (!dst || !src)
		return ;
	if (n <= 0)
		return ;
	while ((src[i]) && (i < (n - 1)))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}