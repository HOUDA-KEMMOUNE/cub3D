/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 04:10:55 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/28 04:10:55 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include "mlx.h"
# include "parsing.h"

# define WIN_WIDTH 1600
# define WIN_HEIGHT 900

/* Key codes */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

/* Movement / rotation */
# define COLLISION_MARGIN 0.05
# define MOVE_SPEED 3.0
# define ROT_SPEED 3.2

/* Math constants */
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define PI 3.14159265358979323846
# define PI_2 1.57079632679489661923
# define PI_3_2 4.71238898038468985769
# define TWO_PI 6.28318530717958647692
# define FOV 1.04719755119659774615

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	angle_offset;
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
}			t_ray;

typedef struct s_img
{
	void	*img;
	void	*addr;
	int		bpp;
	int		line_lenght;
	int		endian;
}			t_img;

typedef struct s_wall_tex
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_lenght;
	int		endian;
	int		width;
	int		height;
}			t_wall_tex;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}			t_mlx;

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
	int	esc;
}			t_keys;

typedef struct s_game
{
	t_player	*player;
	t_texture	*texture;
	t_maze		*maze;
	t_mlx		mlx;
	t_keys		keys;
	t_wall_tex	north_tex;
	t_wall_tex	south_tex;
	t_wall_tex	east_tex;
	t_wall_tex	west_tex;
	double		delta_time;
	long		last_time;
}			t_game;

void		start_cub3d(t_game *game);
void		render_frame(t_game *game);
void		init_player_direction(t_player *player);
void		cast_ray(t_game *game, int x);
void		draw_wall_column(t_game *game, t_ray *ray, int x);
void		my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color);
void		move_forward(t_game *game);
void		move_backward(t_game *game);
void		move_left(t_game *game);
void		move_right(t_game *game);
void		handle_movement(t_game *game);
int			is_valid_position(t_game *game, double x, double y);
void		rotate_left(t_game *game);
void		rotate_right(t_game *game);
void		init_ray(t_ray *ray, t_player *player, int x);
void		calculate_step(t_ray *ray, t_player *player);
void		perform_dda(t_ray *ray, t_maze *maze);
void		calculate_wall_height(t_ray *ray, t_player *player);
long		get_time_ms(void);
void		calculate_delta_time(t_game *game);
void		load_textures(t_game *game);
t_wall_tex	*choose_wall_texture(t_game *game, t_ray *ray);
void		choose_tex_coordinates(t_game *game, t_ray *ray,
				double *wall_x, int *tex_x);
int			key_release(int key_code, t_game *game);
int			key_press(int key_code, t_game *game);
void		check_arg(void *ptr);
int			close_window(t_game *game);
int			loop_hook(t_game *game);
void		cleanup(t_game *game);
void		free_texture_paths(t_game *game);
void		free_map(t_game *game);

#endif