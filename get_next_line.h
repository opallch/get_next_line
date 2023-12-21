/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleung <oleung@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:13:19 by oleung            #+#    #+#             */
/*   Updated: 2023/12/21 11:50:16 by oleung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

char    *get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
char    *extract_line(char *buffer);
void	ft_bzero(void *s, size_t n);
void    update_cache(char *buffer);
char    *append_buffer_to_cache(char *cache, char *buffer);

#endif