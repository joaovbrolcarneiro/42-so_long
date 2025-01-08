# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrol-ca <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 21:20:14 by jbrol-ca          #+#    #+#              #
#    Updated: 2025/01/08 21:20:22 by jbrol-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Directories
SRC_DIR = src
OBJ_DIR = obj
MLX_DIR = mlx
GNL_DIR = GetNextLine
LIBFT_DIR = libft

# Files
NAME = so_long
SRCS = \
	$(SRC_DIR)/free.c \
	$(SRC_DIR)/in_game.c \
	$(SRC_DIR)/movements_collisions.c \
	$(SRC_DIR)/utils2.c \
	$(SRC_DIR)/game.c \
	$(SRC_DIR)/initialize_visited.c \
	$(SRC_DIR)/parse_and_load.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/game_window.c \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/render.c \
	$(SRC_DIR)/validate_map.c \
	$(SRC_DIR)/handle_game.c \
	$(SRC_DIR)/map.c \
	$(SRC_DIR)/update.c \
	$(SRC_DIR)/validation.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

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
