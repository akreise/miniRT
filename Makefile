# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/06 10:54:27 by pshcherb          #+#    #+#              #
#    Updated: 2025/08/23 20:52:11 by pshcherb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = gcc

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = ./mlx/minilibx-linux

BUILD_DIR = build

ifeq ($(DEBUG), 1)
	CFLAGS += -Wall -Wextra -Werror -g -fsanitize=address
else
	CFLAGS += -Wall -Wextra -Werror -fsanitize=address
endif

INCLUDES = -I$(MLX_DIR) -I/usr/local/include $(shell pkg-config --cflags x11)
LDFLAGS += -L$(MLX_DIR) -lmlx -L/usr/X11/lib -lX11 -lXext -lm $(shell pkg-config --libs x11)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LDFLAGS += -L/opt/homebrew/opt/libbsd/lib -lbsd
endif

SRC = \
	src/parser/read_rt_file.c \
	src/parser/id_element.c \
	src/parser/parse_objects.c \
	src/parser/parse_cylinder.c \
	src/parser/parse_ambient.c \
	src/parser/parse_ambient_utils.c \
	src/parser/parse_camera.c \
	src/parser/parse_light.c \
	src/init/init_mlx.c \
	src/math/vec3_add_sub.c \
	src/math/vec3_dot_cross.c \
	src/math/vec3_scalar_normal.c \
	src/math/intersect_sphere.c \
	src/math/intersect_cylinder.c \
	src/math/intersect_plane.c \
	src/math/ray.c \
	src/math/cylinder_utils.c \
	src/scene/light/color_combine.c \
	src/scene/light/lighting_calculation.c \
	src/scene/light/trace_ray.c \
	src/scene/light/trace_objects.c \
	src/scene/light/trace_sphere_plane.c \
	src/scene/light/shadow_utils.c \
	src/scene/light/shadow_checks.c \
	src/scene/light/shadow_factor.c \
	src/scene/light/color_utils.c \
	src/utils/intersect_utils.c \
	src/utils/parsing_utils.c \
	src/render/render.c \
	src/check/check.c \
	src/check/check_utils.c \
	src/check/check_elements.c \
	src/check/check_lighting.c \
	src/check/check_scene.c \
	src/check/check_duplicates.c \
	src/clean/clean.c \
	src/clean/clean_mlx.c \
	src/main/main.c \
	src/main/main_init.c

HEADERS = includes/math_utils.h \
	includes/miniRT.h \
	includes/parser.h \
	includes/render.h \
	includes/scene.h 

# 💡 Преобразуем путь src/foo.c → build/src/foo.o
OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC))
DEPS = $(OBJ:.o=.d)

HIDE = @

BOLD  := \033[1m
GREEN := \033[0;32m
BLUE  := \033[0;34m
RESET := \033[0m
CHECK := ✅
GEAR  := 🔧
BOX   := 📦
TRASH := 🗑
BROOM := 🧹

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) Makefile $(HEADERS)
	@echo "$(GEAR) Linking $(NAME)..."
	@$(MAKE) -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(CHECK) Build complete: $(NAME)$(RESET)"

# 💥 Основной шаблон для сборки .o → из .c
# Создаём директории build/src/... при необходимости
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(HIDE)$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

-include $(DEPS)

$(LIBFT):
	@echo "📚 Building libft..."
	@$(MAKE) -s -C $(LIBFT_DIR) > /dev/null || echo "❌ libft build failed"

clean:
	@echo "$(BROOM) Cleaning object files..."
	$(HIDE)rm -rf $(BUILD_DIR)
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@$(MAKE) -s clean -C $(MLX_DIR)

fclean: clean
	@echo "$(TRASH) Removing binary $(NAME)..."
	$(HIDE)rm -f $(NAME)
	@$(MAKE) -s fclean -C $(LIBFT_DIR)

re: fclean all

debug:
	@$(MAKE) DEBUG=1

.PHONY: all clean fclean re debug
