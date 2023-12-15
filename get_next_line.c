/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleung <oleung@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:12:59 by oleung            #+#    #+#             */
/*   Updated: 2023/12/15 11:28:23 by oleung           ###   ########.fr       */
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
- Line size
- fd can point to not only regular files (what are irregular files?)

Forbidden: lseek(), libft, global variables

Bonus (append the _bonus.[c\h] suffix to the bonus part files.):
- only 1 static var is used
- can manage multiple fd at the same time (array)
*/
// char    *get_next_line(int fd)
// {
//     char    *line;
//     static char    buffer[BUFFER_SIZE];
    
//     if (fd != -1)
//     {
//     // while EOF has not been reached
//         while(read(fd, buffer, BUFFER_SIZE) >= 0) // read() returns number of bytes read
//         {
//             // check if \n in cache
//             if (ft_strchr(buffer, '\n'))
//             {
//                 line = extract_line(buffer);
//                 if (!line)
//                     return (NULL);
//                 update_buffer(buffer);
//                 break;
//             }
//         }
//         // EOF: 
//         // if buffer is not empty: return the rest to the buffer
//         // TODO else: ?
//     return (line);
//     }
// }

// returns everything before the first \n in buffer
char    *extract_line(char *buffer)
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
    line[ft_strlen((const char *) line)] = '\n';
    return (line);
}

// // keeps everything after the first \n in buffer
// void    update_buffer(char *buffer)
// {
//     int     n_char;

//     n_char = 0;
//     while (buffer[n_char] && buffer[n_char] != '\n')
//     {
//         n_char++;
//     }
// }