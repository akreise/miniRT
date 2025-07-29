# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akreise <akreise@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/06 10:54:27 by pshcherb          #+#    #+#              #
#    Updated: 2025/07/29 14:59:15 by akreise          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = gcc
CFLAGS += -Wall -Wextra -Werror -I/usr/local/include -I$(MLX_DIR) $(shell pkg-config --cflags x11) -g -fsanitize=address
LDFLAGS += -L$(MLX_DIR) -lmlx -L/usr/X11/lib -lX11 -lXext  -lm -L/opt/homebrew/opt/libbsd/lib -lbsd $(shell pkg-config --libs x11) # Убрал -L/usr/local/lib
SRC = src/parser/read_rt_file.c \
		src/parser/id_element.c \
		src/parser/parse_objects.c \
		src/parser/parse_ambient.c \
		src/init/init_mlx.c \
		src/math/vec3_add_sub.c \
		src/math/vec3_dot_cross.c \
		src/math/vec3_scalar_normal.c \
		src/math/intersect_sphere.c \
		src/math/intersect_cylinder.c \
		src/math/intersect_plane.c \
		src/math/ray.c \
		src/scene/light/color_combine.c \
		src/scene/light/lighting_calculation.c \
		src/scene/light/trace_ray.c \
		src/utils/intersect_utils.c \
		src/utils/parsing_utils.c \
		src/render/render.c \
		clean.c \
		check.c \
		main.c \

LIBFT = libft/libft.a
MLX_DIR = ./mlx/minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext # Возможно, стоит убрать X11 здесь, так как оно уже есть в LDFLAGS
INCLUDES = -I$(MLX_DIR)

OBJ = $(SRC:.c=.o)
DEPS = $(SRC:.c=.d)

all: $(NAME)

$(NAME): Makefile $(OBJ) $(LIBFT)
	@$(MAKE) -C $(MLX_DIR) --no-print-directory
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

-include $(DEPS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

$(LIBFT):
	make -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

clean:
	rm -f $(OBJ) $(DEPS)
	make clean -C libft
	@make clean -C $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re