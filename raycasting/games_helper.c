/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   games_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 01:19:57 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/28 01:19:58 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	key_press(int key_code, t_game *game)
{
	if (key_code == KEY_ESC)
		game->keys.esc = 1;
	else if (key_code == KEY_W)
		game->keys.w = 1;
	else if (key_code == KEY_S)
		game->keys.s = 1;
	else if (key_code == KEY_A)
		game->keys.a = 1;
	else if (key_code == KEY_D)
		game->keys.d = 1;
	else if (key_code == KEY_LEFT)
		game->keys.left = 1;
	else if (key_code == KEY_RIGHT)
		game->keys.right = 1;
	return (0);
}

int	key_release(int key_code, t_game *game)
{
	if (key_code == KEY_ESC)
		game->keys.esc = 0;
	else if (key_code == KEY_W)
		game->keys.w = 0;
	else if (key_code == KEY_S)
		game->keys.s = 0;
	else if (key_code == KEY_A)
		game->keys.a = 0;
	else if (key_code == KEY_D)
		game->keys.d = 0;
	else if (key_code == KEY_LEFT)
		game->keys.left = 0;
	else if (key_code == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	calculate_delta_time(t_game *game)
{
	long	current_time;

	current_time = get_time_ms();
	game->delta_time = (current_time - game->last_time) / 1000.0;
	if (game->delta_time > 0.05)
		game->delta_time = 0.05;
	if (game->delta_time <= 0.0)
		game->delta_time = 0.016;
	game->last_time = current_time;
}

void	handle_movement(t_game *game)
{
	if (game->keys. esc)
		close_window(game);
	if (game->keys.w)
		move_forward(game);
	if (game->keys.s)
		move_backward(game);
	if (game->keys.a)
		move_left(game);
	if (game->keys.d)
		move_right(game);
	if (game->keys.left)
		rotate_left(game);
	if (game->keys.right)
		rotate_right(game);
}
