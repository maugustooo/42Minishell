/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:16:17 by gude-jes          #+#    #+#             */
/*   Updated: 2024/07/22 10:38:43 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file ft_calloc.c
 * @brief Create an array and fill it with null '\0
*/

#include "libft.h"

/**
 * @brief Allocates memory based on the nmemb and size and fills it with null's
 * 
 * @param nmemb Number of elements
 * @param size Size of the array
 * @return void* Pointer to the array
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if ((nmemb > 2147483647 && size != 0) || (size > 2147483647 && nmemb != 0))
		return (0);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

/**@}*/