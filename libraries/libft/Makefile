# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 20:44:31 by jlacerda          #+#    #+#              #
#    Updated: 2025/01/30 21:41:32 by jlacerda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDES_DIR)

SRCS_DIR = ./sources
OBJS_DIR = ./objects
INCLUDES_DIR = ./includes

SOURCES = \
	$(SRCS_DIR)/ft_split.c \
	$(SRCS_DIR)/ft_strchr.c \
	$(SRCS_DIR)/ft_strlen.c \
	$(SRCS_DIR)/ft_strlcpy.c \
	$(SRCS_DIR)/ft_strnstr.c \
	$(SRCS_DIR)/ft_strjoin.c \
	$(SRCS_DIR)/ft_putstr_fd.c \
	
OBJECTS = $(SOURCES:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJECTS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	ar rcs $(NAME) $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re