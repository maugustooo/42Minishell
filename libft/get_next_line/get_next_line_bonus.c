/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:59:37 by gude-jes          #+#    #+#             */
/*   Updated: 2024/05/03 10:10:57 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file get_next_line_bonus.c
 * @brief Reads a line from multiple file descriptor and returns it
*/

#include "../libft.h"

/**
 * @brief Clears the data from buffer and static variable
 * 
 * @param buffer Buffer
 * @param stash Static variable
 * @return char* NULL
*/
char	*free_data(char *stash, char *buffer)
{
	free(stash);
	free(buffer);
	return (NULL);
}

/**
 * @brief Fills the buffer with the line read
 * 
 * @param fd File descriptor
 * @param stash Static variable
 * @return char* Line joined to stash
*/
char	*read_from_file(int fd, char *stash)
{
	char	*buffer;
	int		read_size;

	read_size = BUFFER_SIZE;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	*buffer = 0;
	while (read_size != 0 && !ft_strchr(buffer, '\n'))
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size < 0)
			return (free_data(stash, buffer));
		buffer[read_size] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	if (read_size == -1 || *stash == '\0')
		return (free_data(stash, buffer));
	free(buffer);
	return (stash);
}

/**
 * @brief Handle the leftover from line
 * 
 * @param stash Static variable
 * @return char* Leftover
*/
char	*leftovers(char *stash)
{
	char	*leftover;

	leftover = ft_strndup(stash + ft_strclen(stash, '\n')
			+ 1, ft_strclen(stash, '\0') - ft_strclen(stash, '\n'));
	free (stash);
	if (!leftover)
		return (NULL);
	return (leftover);
}

/**
 * @brief Main function to read a line from multiple file descriptors
 * 
 * @param fd File descriptor
 * @return char* Line obtained
*/
char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd])
		stash[fd] = NULL;
	stash[fd] = read_from_file(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	new_line = ft_strndup(stash[fd], ft_strclen(stash[fd], '\n') + 1);
	if (!new_line)
		return (NULL);
	stash[fd] = leftovers(stash[fd]);
	if (!stash[fd])
		free(stash[fd]);
	return (new_line);
}

/**@}*/