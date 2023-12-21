/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleung <oleung@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:12:59 by oleung            #+#    #+#             */
/*   Updated: 2023/12/21 18:25:46 by oleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line(int fd)
{
    char    *line;
    static char *cache;

    if (fd < 0 || BUFFER_SIZE < 1)
        return (NULL);
    cache = read_buffer_to_cache(fd, cache);
    if (!cache)
        return (NULL);
    if (ft_strlen(cache) > 0)
    {
        line = extract_line(cache);
        if (!line)
            return (NULL);
        update_cache(cache);
        return (line);
    }
    else
    {
        if (cache)
            free(cache);
        return (NULL);
    }
}

/*Append read value from buffer to cache.*/
char    *read_buffer_to_cache(int fd, char *cache)
{
    ssize_t n_read_bytes;
    char    buffer[BUFFER_SIZE];
    
    n_read_bytes = 1;
    if (!cache)
    {
        cache = malloc(1);
        cache[0] = 0;
    }
    while (!ft_strchr(cache, '\n') && n_read_bytes != 0)
    {
        n_read_bytes = read(fd, buffer, BUFFER_SIZE);
        if (n_read_bytes < 0)
        {
            if (cache)
                free(cache);
            return (NULL);
        }
        buffer[n_read_bytes] = 0;
        cache = ft_strjoin(cache, buffer);
    }
    return (cache);
}

/* 
Returns everything before the first \n in cache.
Return value includes \n at the end.
*/
char    *extract_line(char *cache)
{
    int     n_char;
    char    *line;

    n_char = 0;
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
void    update_cache(char *cache)
{
    int     i;
    int     j;
    char    *new_cache_val;
    size_t  malloc_size_new_cache;

    i = 0;
    while (cache[i] && cache[i] != '\n')
        i++;
    i++;
    malloc_size_new_cache = ft_strlen(cache) - i + 1;
    if (malloc_size_new_cache <= 0)
    {
        i = 0;
        while (cache[i])
            cache[i++] = 0;
        return;
    }
    j = 0;
    new_cache_val = malloc(malloc_size_new_cache);
    if (!new_cache_val)
        return;
    while (cache[i])
    {
        new_cache_val[j++] = cache[i];
        cache[i++] = 0;
    }
    new_cache_val[j] = 0; 
    ft_strlcpy(cache, new_cache_val, j + 1);
    free(new_cache_val);
}