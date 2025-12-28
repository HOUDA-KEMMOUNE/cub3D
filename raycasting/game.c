/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 04:10:55 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/28 04:11:24 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void	init_keys_and_textures(t_game *game)
{
	game->keys.w = 0;
	game->keys.s = 0;
	game->keys.a = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	game->keys.esc = 0;
	game->last_time = get_time_ms();
	game->delta_time = 0.016;
	game->north_tex.img = NULL;
	game->south_tex.img = NULL;
	game->east_tex.img = NULL;
	game->west_tex.img = NULL;
}

static void	init_mlx_and_image(t_game *game)
{
	game->mlx.mlx = mlx_init();
	check_arg(game->mlx.mlx);
	game->mlx.win = mlx_new_window(game->mlx.mlx, WIN_WIDTH,
			WIN_HEIGHT, "cub3d");
	check_arg(game->mlx.win);
	game->mlx.img.img = mlx_new_image(game->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	check_arg(game->mlx.img.img);
	game->mlx.img.addr = mlx_get_data_addr(game->mlx.img.img,
			&game->mlx.img.bpp, &game->mlx.img.line_lenght,
			&game->mlx.img.endian);
}

static void	init_hooks_and_loop(t_game *game)
{
	load_textures(game);
	init_player_direction(game->player);
	mlx_hook(game->mlx.win, 17, 0, close_window, game);
	mlx_hook(game->mlx.win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx.win, 3, 1L << 1, key_release, game);
	mlx_loop_hook(game->mlx.mlx, loop_hook, game);
	mlx_loop(game->mlx.mlx);
}

void	start_cub3d(t_game *game)
{
	init_keys_and_textures(game);
	init_mlx_and_image(game);
	init_hooks_and_loop(game);
}
