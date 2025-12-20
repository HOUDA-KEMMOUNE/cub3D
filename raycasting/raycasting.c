#include "raycasting.h"

void	calculate_step(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
	}
	
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y;
	}
}

void	perform_dda(t_ray *ray, t_maze *maze)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		
		if (ray->map_y >= 0 && ray->map_y < maze->max_row && 
			ray->map_x >= 0 && maze->map[ray->map_y] && 
			ray->map_x < (int)ft_strlen(maze->map[ray->map_y]))
		{
			if (maze->map[ray->map_y][ray->map_x] == '1')
				ray->hit = 1;
		}
		else
		{
			ray->hit = 1;
		}
	}
}

void	calculate_wall_height(t_ray *ray, t_player *player)
{
	double	distance;
	
	if (ray->side == 0)
	{
		distance = (ray->map_x - player->pos_x + 
			(1.0 - ray->step_x) / 2.0) / ray->ray_dir_x;
	}
	else
	{
		distance = (ray->map_y - player->pos_y + 
			(1.0 - ray->step_y) / 2.0) / ray->ray_dir_y;
	}
	ray->perp_wall_dist = distance * cos(ray->angle_offset);
	if (fabs(ray->perp_wall_dist) < 0.001)
		ray->perp_wall_dist = 0.001;
	
	if (ray->perp_wall_dist < 0)
		ray->perp_wall_dist = -ray->perp_wall_dist;
	
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

unsigned int	get_wall_color(t_ray *ray)
{
	unsigned int	color;

	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			color = 0xFF0000;
		else
			color = 0x00FF00;
	}
	else
	{
		if (ray->step_y > 0)
			color = 0x0000FF;
		else
			color = 0xFFFF00;
	}
	
	return (color);
}

void	draw_wall_column(t_game *game, t_ray *ray, int x)
{
	int				y;
	unsigned int	color;

	color = get_wall_color(ray);
	
	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(&game->mlx. img, x, y, 0x87CEEB);
		y++;
	}
	
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		my_mlx_pixel_put(&game->mlx.img, x, y, color);
		y++;
	}
	
	y = ray->draw_end + 1;
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&game->mlx. img, x, y, 0x228B22);
		y++;
	}
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