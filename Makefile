# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/06 10:54:27 by pshcherb          #+#    #+#              #
#    Updated: 2025/05/12 14:42:20 by pshcherb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = gcc
CFLAGS = -Wall -Wextra -Werror 
SRC = src/parser/read_rt_file.c \
		src/parser/id_element.c \
		src/parser/parse_objects.c \
		src/parser/parse_ambient.c \
		src/parser/parsing_utils.c \
		src/math/vec3_add_sub.c \
		src/math/vec3_dot_cross.c \
		src/math/vec3_scalar_normal.c \
		main.c \

LIBFT = libft/libft.a

OBJ = $(SRC:.c=.o)

DEPS = $(SRC:.c=.d)

all: $(NAME)

$(NAME): Makefile $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lm -o $(NAME) 

-include $(DEPS)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

$(LIBFT):
	make -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

clean:
	rm -f $(OBJ) $(DEPS)
	make clean -C libft

re: fclean all

.PHONY: all clean fclean re