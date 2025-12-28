/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 04:35:11 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/28 04:35:13 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	init_player_direction(t_player *player)
{
	if (player->type == north || player->p == 'N')
		player->angle = 3 * M_PI / 2;
	else if (player->type == south || player->p == 'S') 
		player->angle = M_PI / 2;
	else if (player->type == east || player->p == 'E')
		player->angle = 0;
	else if (player->type == west || player->p == 'W')
		player->angle = M_PI;
}

void	init_ray(t_ray *ray, t_player *player, int x)
{
	double	ray_angle;

	ray_angle = player->angle - (FOV / 2.0) + ((double)x / WIN_WIDTH) * FOV;
	ray->angle_offset = ray_angle - player->angle;
	ray->ray_dir_x = cos(ray_angle);
	ray->ray_dir_y = sin(ray_angle);
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
	ray->hit = 0;
}
