# Exit
NAME = so_long

# Compilation
CC = gcc
CFLAGS = -Wall -Werror -Wextra

LIBFT_DIR = libft/

# Checking OS
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    MLX_DIR = ./minilibx-linux
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
else
    MLX_DIR = ./minilibx_opengl_20191021
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

# Sources
SRC = src/so_long.c # Añade aquí tus archivos .c

OBJS = $(SRC:.c=.o)

# Linking
INCLUDE = -I$(MLX_DIR) -I$(LIBFT_DIR)/includes -L$(LIBFT_DIR) -lft $(MLX_FLAGS)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)
	@echo "✅ Compilation finished!"

# Recompile object files if pipex.h changes  
$(OBJS): includes/so_long.h

# Default target for compilation
all: $(NAME)

# Compile object files
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean objects
clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	rm -f $(OBJS)

# Clean objects and executable
fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

# Clean and recompile everything
re: fclean all

# Key words
.PHONY: all clean fclean re