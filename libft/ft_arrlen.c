/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:38:00 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/26 11:48:06 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_arrlen.c
 * @brief Gets he length of an array
*/

#include "libft.h"

/**
 * @brief Get the length of an array
 * 
 * @param arr Array to get the length of
 * @return size_t Length of arr
 */
size_t	ft_arrlen(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

/**@}*/