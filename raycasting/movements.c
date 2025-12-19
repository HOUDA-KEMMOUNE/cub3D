#include "raycasting.h"

// Rotate camera left (counterclockwise)
void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	
	// Rotate direction vector
	old_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(-ROT_SPEED) - 
		game->player->dir_y * sin(-ROT_SPEED);
	game->player->dir_y = old_dir_x * sin(-ROT_SPEED) + 
		game->player->dir_y * cos(-ROT_SPEED);
	
	// Rotate camera plane
	old_plane_x = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * cos(-ROT_SPEED) - 
		game->player->plane_y * sin(-ROT_SPEED);
	game->player->plane_y = old_plane_x * sin(-ROT_SPEED) + 
		game->player->plane_y * cos(-ROT_SPEED);
}

// Rotate camera right (clockwise)
void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	// Rotate direction vector
	old_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(ROT_SPEED) - 
		game->player->dir_y * sin(ROT_SPEED);
	game->player->dir_y = old_dir_x * sin(ROT_SPEED) + 
		game->player->dir_y * cos(ROT_SPEED);
	
	// Rotate camera plane
	old_plane_x = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * cos(ROT_SPEED) - 
		game->player->plane_y * sin(ROT_SPEED);
	game->player->plane_y = old_plane_x * sin(ROT_SPEED) + 
		game->player->plane_y * cos(ROT_SPEED);
}

// Move forward in the direction player is facing
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player->pos_x + game->player->dir_x * MOVE_SPEED;
	new_y = game->player->pos_y + game->player->dir_y * MOVE_SPEED;
	
	// Collision detection
	if (game->maze->map[(int)new_y][(int)game->player->pos_x] != '1')
		game->player->pos_y = new_y;
	if (game->maze->map[(int)game->player->pos_y][(int)new_x] != '1')
		game->player->pos_x = new_x;
}

// Move backward (opposite of forward)
void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player->pos_x - game->player->dir_x * MOVE_SPEED;
	new_y = game->player->pos_y - game->player->dir_y * MOVE_SPEED;
	
	if (game->maze->map[(int)new_y][(int)game->player->pos_x] != '1')
		game->player->pos_y = new_y;
	if (game->maze->map[(int)game->player->pos_y][(int)new_x] != '1')
		game->player->pos_x = new_x;
}

// Strafe left (perpendicular to view direction)
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	// Move perpendicular to direction (use plane vector)
	new_x = game->player->pos_x - game->player->plane_x * MOVE_SPEED;
	new_y = game->player->pos_y - game->player->plane_y * MOVE_SPEED;
	
	if (game->maze->map[(int)new_y][(int)game->player->pos_x] != '1')
		game->player->pos_y = new_y;
	if (game->maze->map[(int)game->player->pos_y][(int)new_x] != '1')
		game->player->pos_x = new_x;
}

// Strafe right
void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player->pos_x + game->player->plane_x * MOVE_SPEED;
	new_y = game->player->pos_y + game->player->plane_y * MOVE_SPEED;
	
	if (game->maze->map[(int)new_y][(int)game->player->pos_x] != '1')
		game->player->pos_y = new_y;
	if (game->maze->map[(int)game->player->pos_y][(int)new_x] != '1')
		game->player->pos_x = new_x;
}