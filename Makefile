# Exit
NAME = so_long

# Compilation
CC = gcc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address

# Directories
LIBFT_DIR = ./libft/
GNL_DIR = ./gnl/
MLX42_DIR = ./MLX42
MLX42_BUILD_LINUX = $(MLX42_DIR)/$(BUILD_DIR)/libmlx42.a
MLX42_BUILD_MACOS = $(MLX42_DIR)/$(BUILD_DIR)/libmlx42.a

# Detecting the OS for MLX42 and GLFW
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    BUILD_DIR = build_linux
    MLX42_BUILD = $(MLX42_DIR)/$(BUILD_DIR)/libmlx42.a
    MLX42_FLAGS = -L$(MLX42_DIR)/build_linux -lmlx42 -lglfw -lm -ldl
    INCLUDE = -I$(MLX42_DIR)/include/MLX42 -I/usr/include -I$(LIBFT_DIR) -I$(GNL_DIR)
else ifeq ($(UNAME_S), Darwin)
	BUILD_DIR = build_macos
    MLX42_BUILD = $(MLX42_DIR)/$(BUILD_DIR)/libmlx42.a
	MLX42_FLAGS = -L/opt/homebrew/Cellar/glfw/3.4/lib -lglfw \
                  -L$(MLX42_DIR)/build_macos -lmlx42 \
                  -framework Cocoa -framework OpenGL -framework IOKit
    INCLUDE = -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX42_DIR)/include/MLX42 \
              -I/opt/homebrew/Cellar/glfw/3.4/include
else
$(error ❌ Unsupported OS: $(UNAME_S))
endif

# Sources
SRC = src/main.c src/prints.c src/map_init.c src/map_elements.c src/map_check.c \
	  src/so_long.c src/player_collectibles.c gnl/get_next_line.c gnl/get_next_line_utils.c

OBJS = $(SRC:.c=.o)

# Build the executable
$(NAME): $(MLX42_BUILD) $(OBJS)
	@make -C $(LIBFT_DIR) --silent
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -L$(LIBFT_DIR) -lft $(MLX42_FLAGS) -o $(NAME)
	@echo "✅ Compilation finished!"

# Ensure MLX42 is built before compiling so_long
$(MLX42_BUILD):
	@echo "⚙️  Compiling MLX42 for $(UNAME_S)..."
	@bash build_mlx42.sh

# Recompile object files if so_long.h changes
$(OBJS): include/so_long.h

# Default target for compilation
all: $(NAME)

# Compile object files
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Clean objects
clean:
	@make -s clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)
	@echo "🧹 Objects cleaned!"

# Clean objects and executable
fclean: clean
	@make -s fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "🧹 Executable cleaned!"

# Clean and recompile everything
re: fclean all

# Key words
.PHONY: all clean fclean re
