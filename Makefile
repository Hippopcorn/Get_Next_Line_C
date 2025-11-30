# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elsa <elsa@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/13 11:40:40 by evarache          #+#    #+#              #
#    Updated: 2025/11/30 20:58:22 by elsa             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SANITIZE = -fsanitize=address,undefined -fno-omit-frame-pointer -g3
SOURCES = get_next_line.c get_next_line_utils.c tests/unity/unity.c tests/gnl_tests.c
OBJECTS = $(SOURCES:.c=.o)
NAME = gnl

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(SANITIZE) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(SANITIZE) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: re
	./$(NAME)

.PHONY: all clean fclean re test
