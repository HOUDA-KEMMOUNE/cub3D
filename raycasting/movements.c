/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 01:10:00 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/28 01:10:03 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	is_valid_position(t_game *game, double x, double y)
{
	if ((int)y < 0 || (int)y >= game->maze->max_row)
		return (0);
	if ((int)x < 0 || !game->maze->map[(int)y])
		return (0);
	if ((int)x >= (int)ft_strlen(game->maze->map[(int)y]))
		return (0);
	if (game->maze->map[(int)y][(int)x] == '1')
		return (0);
	if (game->maze->map[(int)(y - COLLISION_MARGIN)]
		[(int)(x - COLLISION_MARGIN)] == '1')
		return (0);
	if (game->maze->map[(int)(y - COLLISION_MARGIN)]
		[(int)(x + COLLISION_MARGIN)] == '1')
		return (0);
	if (game->maze->map[(int)(y + COLLISION_MARGIN)]
		[(int)(x - COLLISION_MARGIN)] == '1')
		return (0);
	if (game->maze->map[(int)(y + COLLISION_MARGIN)]
		[(int)(x + COLLISION_MARGIN)] == '1')
		return (0);
	return (1);
}

void	rotate_left(t_game *game)
{
	double	rot_speed;

	rot_speed = ROT_SPEED * game->delta_time;
	game->player->angle -= rot_speed;
	if (game->player->angle < 0)
		game->player->angle += TWO_PI;
}

void	rotate_right(t_game *game)
{
	double	rot_speed;

	rot_speed = ROT_SPEED * game->delta_time;
	game->player->angle += rot_speed;
	if (game->player->angle >= TWO_PI)
		game->player->angle -= TWO_PI;
}

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	dir_x;
	double	dir_y;
	double	speed;

	dir_x = cos(game->player->angle);
	dir_y = sin(game->player->angle);
	speed = MOVE_SPEED * game->delta_time;
	new_x = game->player->pos_x + dir_x * speed;
	new_y = game->player->pos_y + dir_y * speed;
	if (is_valid_position(game, new_x, new_y))
	{
		game->player->pos_x = new_x;
		game->player->pos_y = new_y;
	}
}
