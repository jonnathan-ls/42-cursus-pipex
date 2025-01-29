NAME = pipex

SRCS_DIR = ./sources
OBJS_DIR = ./objects
INCLUDES_DIR = ./includes
LIBS_DIR = ./libraries

SOURCES = \
	$(SRCS_DIR)/utils.c \
	$(SRCS_DIR)/pipex.c \
	$(SRCS_DIR)/path_utils.c \
	$(SRCS_DIR)/process_utils.c

OBJECTS = $(SOURCES:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

LIBFT_DIR = $(LIBS_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_DIR = $(LIBS_DIR)/printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES_DIR) -I$(LIBFT_DIR)/includes -I$(PRINTF_DIR)/includes

all: $(LIBFT) $(PRINTF) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

$(NAME): $(OBJECTS) $(LIBFT) $(PRINTF) $(MLX)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(PRINTF) $(LDFLAGS) -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re