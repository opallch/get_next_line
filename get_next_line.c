/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleung <oleung@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:12:59 by oleung            #+#    #+#             */
/*   Updated: 2023/12/17 12:12:39 by oleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
Reads a text file pointed by fd (also standard input) one line at a time.
Returns the line that was read (including \n, except EOF && does not end with \n).
read(), malloc(), free() are allowed.

Undefined behaviour when:
1. fd changed since the last call whereas read()
has not reached EOF.
2. reading a binary file.

Highlights/ Edge cases:
- Static variable
- Buffer size: test with 1, 9999, 10000000 etc.
- different Line size
- fd can point to not only regular files (what are irregular files?)

Forbidden: lseek(), libft, global variables

Bonus (append the _bonus.[c\h] suffix to the bonus part files.):
- only 1 static var is used
- can manage multiple fd at the same time (array)

Test cases:
1. File
    - empty file
    - line size: 1, 1000, 1000000
    - 
2. 
3.

*/

/*
3 steps:
1. append new buffer value to cache
2. extract line from cache
3. update cache (keep everything after the first \n)
*/
char    *get_next_line(int fd)
{
    char    *line;
    ssize_t n_read_bytes;
    char    buffer[BUFFER_SIZE];
    static char *cache;

    n_read_bytes = read(fd, buffer, BUFFER_SIZE);
    cache = append_buffer_to_cache(cache, buffer);
    printf("53 cache: %s\n", cache);
    while (!ft_strchr(cache, '\n') && n_read_bytes > 0)
    {
        n_read_bytes = read(fd, buffer, BUFFER_SIZE);
        cache = append_buffer_to_cache(cache, buffer);
        printf("57 cache: %s\n", cache);
    }
    line = extract_line(cache);
    if (!line)
        return (NULL);
    update_cache(cache);
    printf("76 updated cache: %s\n", cache);
    return (line);
}

/*Append read value from buffer to cache.*/
char    *append_buffer_to_cache(char *cache, char *buffer)
{
    char    *tmp_cache;
    char    *new_cache;
    if (!cache)
    {
        new_cache = malloc(BUFFER_SIZE + 1);
        ft_strlcpy(new_cache, buffer, BUFFER_SIZE + 1);
    }   
    else
    {   
        tmp_cache = malloc(ft_strlen(cache) + BUFFER_SIZE + 1);
        ft_strlcpy(tmp_cache, cache, ft_strlen(cache) + 1);
        new_cache = ft_strjoin(tmp_cache, buffer);
        free(tmp_cache);
        free(cache);
    }
    return (new_cache);
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