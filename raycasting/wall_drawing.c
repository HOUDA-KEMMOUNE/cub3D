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
	int		y;
	double	wall_x;
	int		tex_x;
	double	step;

	calculate_wall_height(ray, game->player);
	choose_tex_coordinates(game, ray, &wall_x, &tex_x);
	step = (double)choose_wall_texture(game, ray)->height
		/ (double)ray->line_height;
	draw_ceiling(game, x, ray);
	draw_wall(game, ray, x, step);
	draw_floor(game, x, ray);
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

void	draw_ceiling(t_game *game, int x, t_ray *ray)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(&game->mlx.img, x, y, game->texture->c_int);
		y++;
	}
}

void	draw_wall(t_game *game, t_ray *ray, int x, double step)
{
	int			y;
	double		tex_pos;
	int			tex_y;
	char		*pixel;
	t_wall_tex	*tex;

	tex = choose_wall_texture(game, ray);
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2)
		* step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		pixel = tex->addr + (tex_y * tex->line_lenght)
			+ (tex->bpp / 8);
		my_mlx_pixel_put(&game->mlx.img, x, y,
			*(unsigned int *)pixel);
		tex_pos += step;
		y++;
	}
}

void	draw_floor(t_game *game, int x, t_ray *ray)
{
	int	y;

	y = ray->draw_end + 1;
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&game->mlx.img, x, y, game->texture->f_int);
		y++;
	}
}
