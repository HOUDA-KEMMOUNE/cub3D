/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:38:51 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/27 16:38:54 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

t_wall_tex	*choose_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&game->east_tex);
		else
			return (&game->west_tex);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (&game->south_tex);
		else
			return (&game->north_tex);
	}
}

static void	calculate_distance_and_perp(t_ray *ray, t_player *player,
	double *distance)
{
	double	offset;

	if (ray->side == 0)
	{
		offset = (1.0 - ray->step_x) / 2.0;
		*distance = (ray->map_x - player->pos_x + offset) / ray->ray_dir_x;
	}
	else
	{
		offset = (1.0 - ray->step_y) / 2.0;
		*distance = (ray->map_y - player->pos_y + offset) / ray->ray_dir_y;
	}
	ray->perp_wall_dist = *distance * cos(ray->angle_offset);
	if (fabs(ray->perp_wall_dist) < 0.001)
		ray->perp_wall_dist = 0.001;
	if (ray->perp_wall_dist < 0)
		ray->perp_wall_dist = -ray->perp_wall_dist;
}

static void	calculate_draw_values(t_ray *ray)
{
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	if (ray->line_height > WIN_HEIGHT * 10)
		ray->line_height = WIN_HEIGHT * 10;
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	calculate_wall_height(t_ray *ray, t_player *player)
{
	double	distance;

	calculate_distance_and_perp(ray, player, &distance);
	calculate_draw_values(ray);
}

void	choose_tex_coordinates(t_game *game, t_ray *ray,
	double *wall_x, int *tex_x)
{
	t_wall_tex	*tex;

	tex = choose_wall_texture(game, ray);
	if (ray->side == 0)
		*wall_x = game->player->pos_y + ray->perp_wall_dist
			* ray->ray_dir_y;
	else
		*wall_x = game->player->pos_x + ray->perp_wall_dist
			* ray->ray_dir_x;
	*wall_x -= floor(*wall_x);
	*tex_x = (int)(*wall_x * (double)tex->width);
	if (*tex_x < 0)
		*tex_x = 0;
	if (*tex_x >= tex->width)
		*tex_x = tex->width - 1;
	if (ray->side == 0 && ray->ray_dir_x > 0)
		*tex_x = tex->width - *tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		*tex_x = tex->width - *tex_x - 1;
}
