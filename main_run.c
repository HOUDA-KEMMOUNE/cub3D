/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:30:00 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/22 11:30:02 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_helper.h"

static void	init_game_struct(t_game *game)
{
	game->texture = malloc(sizeof(t_texture));
	game->player = malloc(sizeof(t_player));
	game->maze = malloc(sizeof(t_maze));
	if (!game->texture || !game->player || !game->maze)
	{
		printf("Error\nMemory allocation failed\n");
		exit(1);
	}
}

static void	parse_and_load(t_game *game, int fd, char *filename)
{
	parsing_directions(fd);
	if (parse_fc_color(filename) == 0)
		exit(1);
	textures_init(filename, game->texture);
	game->texture->c_int = rgb_to_int(game->texture->c);
	game->texture->f_int = rgb_to_int(game->texture->f);
}

static void	validate_and_build(t_game *game, char *filename)
{
	check_if_map_exist(filename);
	check_map_position(filename);
	map_parsing(filename, game->maze, game->player);
	gnl_cleanup();
	init_player_direction(game->player);
}

void	run_game(char *filename)
{
	int		fd;
	t_game	game;

	fd = open(filename, O_RDONLY);
	check_open(fd);
	init_game_struct(&game);
	parse_and_load(&game, fd, filename);
	validate_and_build(&game, filename);
	start_cub3d(&game);
}
