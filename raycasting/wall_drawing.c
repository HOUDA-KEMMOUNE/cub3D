/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:38:51 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/27 16:38:54 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	draw_wall_column(t_game *game, t_ray *ray, int x)
{
	calculate_wall_height(ray, game->player);
	to_draw_ceiling(game, x, ray);
	to_draw_wall(game, ray, x);
	to_draw_floor(game, x, ray);
}

void	cast_ray(t_game *game, int x)
{
	t_ray	ray;

	init_ray(&ray, game->player, x);
	calculate_step(&ray, game->player);
	perform_dda(&ray, game->maze);
	calculate_wall_height(&ray, game->player);
	draw_wall_column(game, &ray, x);
}

static void	to_draw_ceiling(t_game *game, int x, t_ray *ray)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(&game->mlx.img, x, y, game->texture->c_int);
		y++;
	}
}

static void	to_draw_wall(t_game *game, t_ray *ray, int x)
{
	t_wall_tex	*tex;
	double		step;
	double		tex_pos;
	int			pos[2];
	int			tex_y;

	tex = choose_wall_texture(game, ray);
	choose_tex_coordinates(game, ray, &tex_pos, &pos[0]);
	step = (double)tex->height / (double)ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2)
		* step;
	pos[1] = ray->draw_start;
	while (pos[1] <= ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		my_mlx_pixel_put(&game->mlx.img, x, pos[1],
			*(unsigned int *)(tex->addr + (tex_y * tex->line_lenght)
				+ (pos[0] * (tex->bpp / 8))));
		tex_pos += step;
		pos[1]++;
	}
}

static void	to_draw_floor(t_game *game, int x, t_ray *ray)
{
	int	y;

	y = ray->draw_end + 1;
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&game->mlx.img, x, y, game->texture->f_int);
		y++;
	}
}
