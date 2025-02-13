# Exit
NAME = so_long

# Compilation
CC = gcc
CFLAGS = -Wall -Werror -Wextra

# Directories
LIBFT_DIR = libft/
MLX42_DIR = MLX42/

# Library and flags
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    MLX_FLAGS = -L$(MLX42_DIR) -lmlx42 -ldl -lglfw -lm
else
    MLX_FLAGS = -L$(MLX42_DIR) -lmlx42 -framework Cocoa -framework OpenGL -framework IOKit
endif

# Sources
SRC = src/so_long.c # Añade aquí más archivos .c si tienes
OBJS = $(SRC:.c=.o)

# Linking and building the executable
INCLUDE = -I$(MLX42_DIR)/include/MLX42 -I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ Compilation finished!"

# Recompile object files if so_long.h changes
$(OBJS): includes/so_long.h

# Default target for compilation
all: $(NAME)

# Compile object files
%.o: %.c
	@$(CC) $(CFLAGS) -I$(MLX42_DIR)/include/MLX42 -c $< -o $@

# Clean objects
clean:
	@make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

# Clean objects and executable
fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

# Clean and recompile everything
re: fclean all

# Key words
.PHONY: all clean fclean re