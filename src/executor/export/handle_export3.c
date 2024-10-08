/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:25:31 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/08 11:34:35 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr_free(const char *s, unsigned int start, size_t len)
{
	char	*res;
	char	*src;
	size_t	reslen;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < (size_t)start)
		return (ft_strdup(""));
	src = (char *)s + start;
	if (ft_strlen(src) < len)
		reslen = ft_strlen(src) + 1;
	else
		reslen = len + 1;
	res = malloc(reslen * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, src, reslen);
	free(src);
	return (res);
}
