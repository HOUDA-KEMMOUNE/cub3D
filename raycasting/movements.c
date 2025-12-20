#include "raycasting.h"

// Rotate left - now uses delta_time! 
void	rotate_left(t_game *game)
{
	double	rot_speed;
	
	// Calculate rotation for this frame
	// ROT_SPEED is "per second", so multiply by delta_time
	rot_speed = ROT_SPEED * game->delta_time;
	
	game->player->angle -= rot_speed;
	
	if (game->player->angle < 0)
		game->player->angle += TWO_PI;
}

// Rotate right - now uses delta_time!
void	rotate_right(t_game *game)
{
	double	rot_speed;
	
	rot_speed = ROT_SPEED * game->delta_time;
	
	game->player->angle += rot_speed;
	
	if (game->player->angle >= TWO_PI)
		game->player->angle -= TWO_PI;
}

// Move forward - now uses delta_time! 
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	dir_x;
	double	dir_y;
	double	speed;
	
	dir_x = cos(game->player->angle);
	dir_y = sin(game->player->angle);
	
	// MOVE_SPEED is "per second", so multiply by delta_time
	speed = MOVE_SPEED * game->delta_time;
	
	new_x = game->player->pos_x + dir_x * speed;
	new_y = game->player->pos_y + dir_y * speed;
	
	if (game->maze->map[(int)new_y][(int)game->player->pos_x] != '1')
		game->player->pos_y = new_y;
	if (game->maze->map[(int)game->player->pos_y][(int)new_x] != '1')
		game->player->pos_x = new_x;
}

// Move backward - now uses delta_time!
void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	dir_x;
	double	dir_y;
	double	speed;
	
	dir_x = cos(game->player->angle);
	dir_y = sin(game->player->angle);
	
	speed = MOVE_SPEED * game->delta_time;
	
	new_x = game->player->pos_x - dir_x * speed;
	new_y = game->player->pos_y - dir_y * speed;
	
	if (game->maze->map[(int)new_y][(int)game->player->pos_x] != '1')
		game->player->pos_y = new_y;
	if (game->maze->map[(int)game->player->pos_y][(int)new_x] != '1')
		game->player->pos_x = new_x;
}

// Strafe left - now uses delta_time!
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;
	double	strafe_angle;
	double	speed;
	
	strafe_angle = game->player->angle - PI_2;
	speed = MOVE_SPEED * game->delta_time;
	
	new_x = game->player->pos_x + cos(strafe_angle) * speed;
	new_y = game->player->pos_y + sin(strafe_angle) * speed;
	
	if (game->maze->map[(int)new_y][(int)game->player->pos_x] != '1')
		game->player->pos_y = new_y;
	if (game->maze->map[(int)game->player->pos_y][(int)new_x] != '1')
		game->player->pos_x = new_x;
}

// Strafe right - now uses delta_time!
void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;
	double	strafe_angle;
	double	speed;
	
	strafe_angle = game->player->angle + PI_2;
	speed = MOVE_SPEED * game->delta_time;
	
	new_x = game->player->pos_x + cos(strafe_angle) * speed;
	new_y = game->player->pos_y + sin(strafe_angle) * speed;
	
	if (game->maze->map[(int)new_y][(int)game->player->pos_x] != '1')
		game->player->pos_y = new_y;
	if (game->maze->map[(int)game->player->pos_y][(int)new_x] != '1')
		game->player->pos_x = new_x;
}