/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:59:35 by gude-jes          #+#    #+#             */
/*   Updated: 2024/08/20 15:04:22 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @defgroup mandatory Mandatory
 * @{
 * @file get_next_line_utils_bonus.c
 * @brief Utils for get_next_line_bonus.c 
*/

#include "../libft.h"

/**
 * @brief Checks if the string has a character
 * 
 * @param str String
 * @param c Character
 * @return char* Position of character in string
*/
char	*gnl_ft_strchr(char *str, char c)
{
	int	i;
	int	size;

	if (!str)
		return (NULL);
	i = 0;
	size = ft_strclen(str, '\0');
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	if (c == '\0')
		return (str + i);
	if (size <= i)
		return (NULL);
	return (str + i);
}

/**
 * @brief Concatenates s1 and s2 and returns a new string
 * 
 * @param s1 First String
 * @param s2 Second String
 * @return char* New string
*/
char	*gnl_ft_strjoin(char *s1, char *s2)
{
	char	*newstring;
	int		i;
	int		j;
	int		size;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		s1[0] = '\0';
	}
	size = ft_strclen(s1, '\0') + ft_strclen(s2, '\0');
	newstring = malloc(sizeof(char *) * (size + 1));
	if (!newstring)
		return (0);
	i = -1;
	j = 0;
	while ((i < size) && (s1[++i]))
		newstring[i] = s1[i];
	while ((i < size) && (s2[j]))
		newstring[i++] = s2[j++];
	newstring[i] = '\0';
	if (s1)
		free (s1);
	return (newstring);
}

/**
 * @brief Duplicate a string
 * 
 * @param s String
 * @param len Length to duplicate
 * @return char* New string
*/
char	*ft_strndup(char *s, int len)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	if (!str)
		return (0);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/**@}*/