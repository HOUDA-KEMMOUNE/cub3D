#ifndef RAYCASTING_H
# define RAYCASTING_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
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

// Movement/Rotation
# define MOVE_SPEED 3.0
# define ROT_SPEED 3.2       // Rotation speed in radians (~4 degrees)

// Math constants
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

# define PI M_PI
# define PI_2 (M_PI / 2.0)       // 90 degrees
# define PI_3_2 (3.0 * M_PI / 2.0) // 270 degrees
# define TWO_PI (2.0 * M_PI)     // 360 degrees

// Field of View (FOV) - adjust this to change how wide you can see
// 60 degrees = M_PI / 3.0 (standard Wolfenstein)
// 66 degrees ≈ 1.15 radians (similar to your old plane_x = 0.66)dddddd
# define FOV (M_PI / 3.0)        // 60 degrees

// Ray structure
typedef struct s_ray
{
	double	ray_dir_x;           // Ray direction X component
	double	ray_dir_y;           // Ray direction Y component
	double	angle_offset;		 // angle diff from player
	int		map_x;               // Current map cell X
	int		map_y;               // Current map cell Y
	double	side_dist_x;         // Distance to next X grid line
	double	side_dist_y;         // Distance to next Y grid line
	double	delta_dist_x;        // Distance between X grid lines
	double	delta_dist_y;        // Distance between Y grid lines
	double	perp_wall_dist;      // Perpendicular distance to wall
	int		step_x;              // Step direction in X (-1 or +1)
	int		step_y;              // Step direction in Y (-1 or +1)
	int		hit;                 // Did we hit a wall?
	int		side;                // 0 = vertical wall, 1 = horizontal wall
	int		line_height;         // Height of wall slice to draw
	int		draw_start;          // Start Y position for drawing
	int		draw_end;            // End Y position for drawing
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

typedef struct s_keys
{
	int	w;           // Forward
	int	s;           // Backward
	int	a;           // Strafe left
	int	d;           // Strafe right
	int	left;        // Rotate left
	int	right;       // Rotate right
	int	esc;         // Exit
}	t_keys;

typedef struct	s_game
{
	t_player	*player;
	t_texture	*texture;
	t_maze		*maze;
	t_mlx		mlx;
	t_keys		keys;
	double		delta_time;    // 🆕 Time since last frame (seconds)
	long		last_time;     // 🆕 Timestamp of last frame (milliseconds)
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
long	get_time_ms(void);      
void	calculate_delta_time(t_game *game); 

#endif