#ifndef RAYCASTING_H
# define RAYCASTING_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "parsing.h"

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

// Key codes
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

// Movement/Rotation in radians
# define MOVE_SPEED 0.07
# define ROT_SPEED 0.07          // Rotation speed in radians (~2. 86 degrees)

// Math constants (if not in math.h)
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

# define PI M_PI
# define PI_2 (M_PI / 2.0)       // 90 degrees
# define PI_3_2 (3.0 * M_PI / 2.0) // 270 degrees
# define TWO_PI (2.0 * M_PI)     // 360 degrees

// Rest of the structures... 
typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct	s_img
{
	void	*img;
	void	*addr;
	int		bpp;
	int		line_lenght;
	int		endian;
}				t_img;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}				t_mlx;

typedef struct	s_game
{
	t_player	*player;
	t_texture	*texture;
	t_maze		*maze;
	t_mlx		mlx;
}				t_game;

// Function declarations
void	start_cub3D(t_game *game);
void	render_frame(t_game *game);
void	init_player_direction(t_player *player);
void	cast_ray(t_game *game, int x);
void	draw_wall_column(t_game *game, t_ray *ray, int x);
void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
void	init_ray(t_ray *ray, t_player *player, int x);
void	calculate_step(t_ray *ray, t_player *player);
void	perform_dda(t_ray *ray, t_maze *maze);
void	calculate_wall_height(t_ray *ray, t_player *player);
unsigned int	get_wall_color(t_ray *ray);

#endif