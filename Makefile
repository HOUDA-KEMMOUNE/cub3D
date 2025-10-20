NAME = cub3D
LIBFT = libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c utils.c parsing/parsing_color.c parsing/parsing_directions.c\
	  parsing/map_parsing.c

GNL_SRC = get_next_line/get_next_line.c
GNL_OBJ = $(GNL_SRC:.c=.o)

ALL_SRC = $(SRC) $(GNL_SRC)
OBJ = $(ALL_SRC:.c=.o)
INCLUDES = -I. -I./libft -I./get_next_line -I./parsing

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIBFT)

clean:
	@rm -rf $(OBJ) $(GNL_OBJ)
	@make clean -C libft

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft

re: fclean all
