/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleung <oleung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:12:59 by oleung            #+#    #+#             */
/*   Updated: 2023/12/14 20:05:45 by oleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line(int fd)
{
    char    *line;
    static char    buffer[BUFFER_SIZE];
    
    if (fd != -1)
    {
    // while EOF has not been reached
        while(read(fd, buffer, BUFFER_SIZE) >= 0) // read() returns number of bytes read
        {
            // check if \n in cache
            if (ft_strchr(buffer, '\n'))
            {
                line = extract_line(buffer);
                if (!line)
                    return (NULL);
                update_buffer(buffer);
                break;
            }
        }
        // EOF: 
        // if buffer is not empty: return the rest to the buffer
        // TODO else: ?
    return (line);
    }
}

// returns everything before the first \n in buffer
static char    *extract_line(char *buffer)
{
    int     n_char;
    char    *line;

    n_char = 0;
    while (buffer[n_char] && buffer[n_char] != '\n')
    {
        n_char++;
    }
    line = malloc(++n_char);
    if (!line)
        return (NULL);
    ft_strlcpy(line, buffer, n_char);
    return (line);
}

// keeps everything after the first \n in buffer
static void    update_buffer(char *buffer)
{
    int     n_char;

    n_char = 0;
    while (buffer[n_char] && buffer[n_char] != '\n')
    {
        n_char++;
    }
}