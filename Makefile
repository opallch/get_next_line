# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oleung <oleung@student.42berlin.de>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/12 09:17:28 by oleung            #+#    #+#              #
#    Updated: 2023/12/12 09:18:14 by oleung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar r
RM = rm -rf

SRCS = 	get_next_line.c \
		get_next_line_utils.c
	
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

norm: $(SRCS)
	norminette *.c *.h

format: $(SRCS)
	python3 -m c_formatter_42 *.c *.h
	make norm

.PHONY: bonus all clean fclean re norm format