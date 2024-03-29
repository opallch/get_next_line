/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleung <oleung@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:12:59 by oleung            #+#    #+#             */
/*   Updated: 2023/12/21 22:02:50 by oleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*cache;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!cache)
	{
		cache = (char *)malloc(1);
		cache[0] = 0;
	}
	cache = read_buffer_to_cache(fd, cache);
	if (!cache)
		return (NULL);
	line = extract_line(cache);
	cache = update_cache(cache);
	return (line);
}

/*Append read value from buffer to cache.*/
char	*read_buffer_to_cache(int fd, char *cache)
{
	ssize_t	n_read_bytes;
	char	*buffer;

	n_read_bytes = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!cache || !buffer)
		return (NULL);
	while (!ft_strchr(cache, '\n') && n_read_bytes != 0)
	{
		n_read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (n_read_bytes < 0)
		{
			free(cache);
			free(buffer);
			return (NULL);
		}
		buffer[n_read_bytes] = 0;
		cache = ft_strjoin(cache, buffer);
	}
	free(buffer);
	return (cache);
}

/*
Returns everything before the first \n in cache.
Return value includes \n at the end.
*/
char	*extract_line(char *cache)
{
	int		n_char;
	char	*line;

	n_char = 0;
	if (!cache[n_char])
		return (NULL);
	while (cache[n_char] && cache[n_char] != '\n')
	{
		n_char++;
	}
	n_char += 2;
	line = malloc(n_char);
	if (!line)
		return (NULL);
	ft_strlcpy(line, cache, n_char);
	return (line);
}

// keeps everything after the first \n in cache
char	*update_cache(char *cache)
{
	int		i;
	int		j;
	char	*new_cache;

	i = 0;
	while (cache[i] && cache[i] != '\n')
		i++;
	if (!cache[i])
	{
		free(cache);
		return (NULL);
	}
	new_cache = malloc(ft_strlen(cache) - i + 1);
	if (!new_cache)
		return (NULL);
	j = 0;
	i++;
	while (cache[i])
		new_cache[j++] = cache[i++];
	new_cache[j] = 0;
	free(cache);
	return (new_cache);
}
