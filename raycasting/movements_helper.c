/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 01:10:34 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/28 01:10:37 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	dir_x;
	double	dir_y;
	double	speed;

	dir_x = cos(game->player->angle);
	dir_y = sin(game->player->angle);
	speed = MOVE_SPEED * game->delta_time;
	new_x = game->player->pos_x - dir_x * speed;
	new_y = game->player->pos_y - dir_y * speed;
	if (is_valid_position(game, new_x, new_y))
	{
		game->player->pos_x = new_x;
		game->player->pos_y = new_y;
	}
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;
	double	strafe_angle;
	double	speed;

	strafe_angle = game->player->angle - PI_2;
	speed = MOVE_SPEED * game->delta_time;
	new_x = game->player->pos_x + cos(strafe_angle) * speed;
	new_y = game->player->pos_y + sin(strafe_angle) * speed;
	if (is_valid_position(game, new_x, new_y))
	{
		game->player->pos_x = new_x;
		game->player->pos_y = new_y;
	}
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;
	double	strafe_angle;
	double	speed;

	strafe_angle = game->player->angle + PI_2;
	speed = MOVE_SPEED * game->delta_time;
	new_x = game->player->pos_x + cos(strafe_angle) * speed;
	new_y = game->player->pos_y + sin(strafe_angle) * speed;
	if (is_valid_position(game, new_x, new_y))
	{
		game->player->pos_x = new_x;
		game->player->pos_y = new_y;
	}
}
