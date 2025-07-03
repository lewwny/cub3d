# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 19:14:45 by lenygarcia        #+#    #+#              #
#    Updated: 2025/07/03 09:58:36 by lengarci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g #-fsanitize=address

FILES		= main.c parsing.c key_hook.c load_img.c extract_map.c \
			utils.c parse_texture.c parse_color.c parse_line.c \
			map_to_finalmap.c parse_map.c init_player.c \
			move_player.c extract_texture.c os.c convert_texture.c \
			raycasting.c
SRC_DIR		= srcs
SRCS		= $(addprefix $(SRC_DIR)/, $(FILES))
OBJ_DIR		= .obj
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

NAME		= cub3d

UNAME_S		= $(shell uname -s)

ifeq ($(UNAME_S),Darwin)  # macOS
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	MLX_DIR = ./mlx_mac
else                       # Linux
	MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lbsd
	MLX_DIR = ./mlx_linux
endif

LIBFT_PATH	= ./libft
LIBFT		= $(LIBFT_PATH)/libft.a
MLX_MAKE	= $(MAKE) -C $(MLX_DIR)

RESET		= \033[0m
GREEN		= \033[0;32m
BLUE		= \033[0;34m
YELLOW		= \033[1;33m
CYAN		= \033[0;36m
RED			= \033[0;31m

all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(YELLOW)==> Compiling libft...$(RESET)\n"
	$(MAKE) -C $(LIBFT_PATH)
	@printf "$(YELLOW)==> Compiling minilibx...$(RESET)\n"
	$(MLX_MAKE)
	@printf "$(GREEN)==> Linking $(NAME)...$(RESET)\n"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(MLX_FLAGS)
	@printf "$(GREEN)✔ Build complete!$(RESET)\n"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(CYAN)Compiling $<...$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@printf "$(BLUE)✔ Clean complete.$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@printf "$(BLUE)✔ Full clean complete.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re