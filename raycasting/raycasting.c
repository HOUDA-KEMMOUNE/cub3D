#include "raycasting.h"

// Initialize ray for current screen column
void	init_ray(t_ray *ray, t_player *player, int x)
{
	double	camera_x;

	// Calculate x-coordinate in camera space (ranges from -1 to +1)
	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	
	// Ray direction based on player direction and camera plane
	ray->ray_dir_x = player->dir_x + player->plane_x * camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * camera_x;
	
	// Starting position in map grid
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	
	// Calculate delta distance (distance ray travels between grid lines)
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;  // Very large number (avoid division by 0)
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	
	ray->hit = 0;
}

// Calculate step direction and initial side distances
void	calculate_step(t_ray *ray, t_player *player)
{
	// Determine X step direction and initial distance
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
	
	// Determine Y step direction and initial distance
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

// Perform DDA (Digital Differential Analysis) algorithm
void	perform_dda(t_ray *ray, t_maze *maze)
{
	while (ray->hit == 0)
	{
		// Jump to next map square, either in x-direction or y-direction
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;  // Hit a North/South wall
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;  // Hit an East/West wall
		}
		
		// Check if ray has hit a wall
		if (ray->map_y >= 0 && ray->map_y < maze->max_row && 
			ray->map_x >= 0 && maze->map[ray->map_y] && 
			maze->map[ray->map_y][ray->map_x] == '1')
		{
			ray->hit = 1;
		}
	}
}

// Calculate perpendicular wall distance and wall height on screen
void	calculate_wall_height(t_ray *ray, t_player *player)
{
	// Calculate perpendicular distance to avoid fisheye effect
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - player->pos_x + 
			(1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->pos_y + 
			(1 - ray->step_y) / 2) / ray->ray_dir_y;
	
	// Calculate height of wall slice on screen
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	
	// Calculate lowest and highest pixel to fill in current stripe
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

// Choose wall color based on direction (temporary, before textures)
unsigned int	get_wall_color(t_ray *ray)
{
	unsigned int	color;

	// Different colors for different wall orientations
	if (ray->side == 0)
	{
		// North/South walls (brighter)
		if (ray->step_x > 0)
			color = 0xFF0000;  // Red (East-facing)
		else
			color = 0x00FF00;  // Green (West-facing)
	}
	else
	{
		// East/West walls (darker for depth perception)
		if (ray->step_y > 0)
			color = 0x0000FF;  // Blue (South-facing)
		else
			color = 0xFFFF00;  // Yellow (North-facing)
	}
	
	return (color);
}

// Draw a vertical wall slice (column) on screen
void	draw_wall_column(t_game *game, t_ray *ray, int x)
{
	int				y;
	unsigned int	color;

	color = get_wall_color(ray);
	
	// Draw ceiling (from top to wall start)
	y = 0;
	while (y < ray->draw_start)
	{
		// Use ceiling color from texture config (parse as int from RGB string)
		my_mlx_pixel_put(&game->mlx. img, x, y, 0x87CEEB);  // Sky blue
		y++;
	}
	
	// Draw wall slice
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		my_mlx_pixel_put(&game->mlx.img, x, y, color);
		y++;
	}
	
	// Draw floor (from wall end to bottom)
	y = ray->draw_end + 1;
	while (y < WIN_HEIGHT)
	{
		// Use floor color from texture config
		my_mlx_pixel_put(&game->mlx.img, x, y, 0x228B22);  // Forest green
		y++;
	}
}

// Main raycasting function - cast one ray per screen column
void	cast_ray(t_game *game, int x)
{
	t_ray	ray;

	init_ray(&ray, game->player, x);
	calculate_step(&ray, game->player);
	perform_dda(&ray, game->maze);
	calculate_wall_height(&ray, game->player);
	draw_wall_column(game, &ray, x);
}