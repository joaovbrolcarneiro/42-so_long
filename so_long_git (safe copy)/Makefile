# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories
SRC_DIR = src
OBJ_DIR = obj
MLX_DIR = mlx
GNL_DIR = GetNextLine
LIBFT_DIR = libft

# Files
NAME = so_long
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# MLX Flags and Includes
INCLUDES = -I$(MLX_DIR) -Iinclude -I$(GNL_DIR) -I$(LIBFT_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11

# Add object files from libft and GetNextLine
LIBFT_OBJS = $(LIBFT_DIR)/libft.a
GNL_OBJS = $(GNL_DIR)/get_next_line.o $(GNL_DIR)/get_next_line_utils.o

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_OBJS) $(GNL_OBJS) $(MLX_DIR)/libmlx.a
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_OBJS) $(GNL_OBJS) $(MLX_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(MLX_DIR)/libmlx.a:
	@make -C $(MLX_DIR)

$(LIBFT_DIR)/libft.a:
	@make -C $(LIBFT_DIR)

bonus: CFLAGS += -DBONUS
bonus: all

clean:
	@make clean -C $(MLX_DIR)
	@make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

