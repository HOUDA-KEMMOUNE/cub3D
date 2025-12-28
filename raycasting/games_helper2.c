/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   games_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 01:22:56 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/28 01:22:58 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	check_arg(void *ptr)
{
	if (ptr == NULL)
	{
		printf("Error\nMLX initialization failed\n");
		exit(1);
	}
}

int	loop_hook(t_game *game)
{
	calculate_delta_time(game);
	handle_movement(game);
	render_frame(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win,
		game->mlx.img.img, 0, 0);
	return (0);
}

int	close_window(t_game *game)
{
	if (game->mlx. mlx)
	{
		if (game->mlx.img.img)
			mlx_destroy_image(game->mlx.mlx, game->mlx.img.img);
		if (game->north_tex.img)
			mlx_destroy_image(game->mlx.mlx, game->north_tex. img);
		if (game->south_tex.img)
			mlx_destroy_image(game->mlx.mlx, game->south_tex.img);
		if (game->east_tex.img)
			mlx_destroy_image(game->mlx.mlx, game->east_tex.img);
		if (game->west_tex. img)
			mlx_destroy_image(game->mlx. mlx, game->west_tex.img);
		if (game->mlx.win)
			mlx_destroy_window(game->mlx.mlx, game->mlx.win);
		mlx_destroy_display(game->mlx.mlx);
		free(game->mlx.mlx);
		game->mlx.mlx = NULL;
	}
	cleanup(game);
	exit(0);
	return (0);
}
