
# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2024/10/30 21:52:12 by jlacerda          #+#    #+#             #
#   Updated: 2024/11/14 01:43:08 by jlacerda         ###   ########.fr       #
#                                                                            #
# ************************************************************************** #

NAME = libftprintf.a

COMPILER = cc
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDES_DIR)

SRCS_DIR = ./sources
OBJS_DIR = ./objects
INCLUDES_DIR = ./includes

SOURCES = \
	$(SRCS_DIR)/ft_printf.c \
	$(SRCS_DIR)/ft_get_chr.c \
	$(SRCS_DIR)/ft_get_str.c \
	$(SRCS_DIR)/ft_get_hex.c \
	$(SRCS_DIR)/ft_get_nbr.c \
	$(SRCS_DIR)/ft_get_ptr.c \
	$(SRCS_DIR)/ft_get_unbr.c \
	$(SRCS_DIR)/ft_set_flags.c \
	$(SRCS_DIR)/ft_set_padding.c \
	$(SRCS_DIR)/ft_set_precision.c \
	$(SRCS_DIR)/ft_utils_chunk_one.c \
	$(SRCS_DIR)/ft_utils_chunk_two.c \

OBJS = $(SOURCES:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(COMPILER) $(CFLAGS) -c $< -o $@
	ar rcs $(NAME) $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
