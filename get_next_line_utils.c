/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleung <oleung@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:13:09 by oleung            #+#    #+#             */
/*   Updated: 2023/12/15 11:21:54 by oleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	c %= 256;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	pos;

	if (size == 0)
	{
		return (ft_strlen(src));
	}
	pos = 0;
	while (src[pos] && pos < size - 1)
	{
		dest[pos] = src[pos];
		pos++;
	}
	dest[pos] = '\0';
	return (ft_strlen(src));
}
