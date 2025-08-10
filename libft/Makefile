# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/18 18:00:47 by pshcherb          #+#    #+#              #
#    Updated: 2025/08/05 23:23:07 by pshcherb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2024/09/18 18:00:47 by pshcherb          #+#    #+#              #
#    Updated: 2025/02/15 12:37:23 by pshcherb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

CC = gcc
FLAGS = -Wall -Werror -Wextra 
BUILD_DIR = build

SRCS =  get_next_line.c \
	get_next_line_utils.c \
	ft_atof.c \
	ft_printf.c \
	ft_printf_utils.c \
	ft_array_count.c \
	ft_strndup.c \
	ft_strnlen.c \
	ft_isspace.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_strcmp.c \
	
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS =  $(SRCS:.c=.d)

all: $(NAME)

$(NAME):    $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(BUILD_DIR)/%.o: %.c Makefile 
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -MMD -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re

-include $(DEPS)