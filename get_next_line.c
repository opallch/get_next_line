/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleung <oleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:12:59 by oleung            #+#    #+#             */
/*   Updated: 2023/12/16 16:47:45 by oleung           ###   ########.fr       */
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
char    *get_next_line(int fd)
{
    char    *line;
    ssize_t n_read_bytes;
    static char    buffer[BUFFER_SIZE];

    n_read_bytes = read(fd, buffer, BUFFER_SIZE);
    while (!ft_strchr(buffer, '\n') && n_read_bytes > 0)
    {
        n_read_bytes = read(fd, buffer, BUFFER_SIZE);
    }
    if (ft_strlen(buffer) > 0)
    {
        line = extract_line(buffer);
        if (!line)
            return (NULL);
        update_buffer(buffer);
    }
    else
        return (NULL);
    return (line);
}

/* 
Returns everything before the first \n in buffer.
Return value includes \n at the end.
*/
char    *extract_line(char *buffer)
{
    int     n_char;
    char    *line;

    n_char = 0;
    while (buffer[n_char] && buffer[n_char] != '\n')
    {
        n_char++;
    }
    n_char += 2;
    line = malloc(n_char);
    if (!line)
        return (NULL);
    ft_strlcpy(line, buffer, n_char);
    return (line);
}

// keeps everything after the first \n in buffer
void    update_buffer(char *buffer)
{
    int     i;
    int     j;
    char    *new_buffer_val;
    size_t  malloc_size_new_buffer;

    i = 0;
    while (buffer[i] && buffer[i] != '\n')
        i++;
    i++;
    malloc_size_new_buffer = ft_strlen(buffer) - i + 1;
    if (malloc_size_new_buffer <= 0)
    {
        i = 0;
        while (buffer[i])
            buffer[i++] = 0;
        return;
    }
    j = 0;
    new_buffer_val = malloc(malloc_size_new_buffer);
    if (!new_buffer_val)
        return;
    while (buffer[i])
    {
        new_buffer_val[j++] = buffer[i];
        buffer[i++] = 0;
    }
    new_buffer_val[j] = 0; 
    ft_strlcpy(buffer, new_buffer_val, j + 1);
    free(new_buffer_val);
}