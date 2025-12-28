NAME = cub3D
LIBFT = libft/libft.a
MLX_DIR = mlx
MLX = $(MLX_DIR)/libmlx.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
MAKEFLAGS += --no-print-directory
QUIET ?= @
SILENT_MAKE = $(QUIET)$(MAKE) -s

SRC = main.c main_helper.c main_run.c utils.c \
	parsing/parsing_color.c parsing/parsing_color_helper.c \
	parsing/parsing_directions.c parsing/parsing_directions_helper.c \
	parsing/map_parsing.c parsing/map_parsing_utils.c \
	parsing/map_parsing_checks.c parsing/map_parsing_extra.c \
	parsing/map_parsing_spaces.c parsing/map_parsing_space_utils.c \
	parsing/map_parsing_player.c parsing/helpers.c parsing/helpers2.c \
	parsing/helpers3.c parsing/helpers4.c parsing/helpers5.c \
	raycasting/game.c raycasting/init.c raycasting/movements.c \
	raycasting/movements_helper.c raycasting/games_helper.c \
	raycasting/games_helper2.c raycasting/raycasting.c \
	raycasting/raycasting_helper.c raycasting/render.c \
	raycasting/textures.c raycasting/wall_drawing.c \
	cleanup.c

GNL_SRC = get_next_line/get_next_line.c
GNL_OBJ = $(GNL_SRC:.c=.o)

ALL_SRC = $(SRC) $(GNL_SRC)
OBJ = $(ALL_SRC:.c=.o)
INCLUDES = -I. -I./libft -I./get_next_line -I./parsing -I$(MLX_DIR)

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	$(SILENT_MAKE) -C libft >/dev/null 2>&1 || { echo "libft build failed"; exit 1; }

$(MLX):
	$(SILENT_MAKE) -C $(MLX_DIR) >/dev/null 2>&1 || { echo "mlx build failed"; exit 1; }

%.o: %.c
	$(QUIET)$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(QUIET)$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIBFT) $(MLX_FLAGS)

clean:
	@rm -rf $(OBJ) $(GNL_OBJ)
	@make clean -C libft
	@make clean -C $(MLX_DIR)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
