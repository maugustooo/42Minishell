/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:20:05 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/18 11:48:13 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_char(char *str, char sep, int n)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < n)
	{
		if (str[i] == sep)
			count++;
		i++;
	}	
	return (count);
}
