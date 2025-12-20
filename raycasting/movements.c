#include "raycasting.h"

//(counterclockwise)
void rotate_left(t_game *game)
{
    // Just subtract from angle! 
    game->player->angle -= ROT_SPEED;
    
    // Keep angle in range [0, 2π]
    if (game->player->angle < 0)
        game->player->angle += 2 * M_PI;
}

//(clockwise)
void rotate_right(t_game *game)
{
    // Just add to angle!
    game->player->angle += ROT_SPEED;
    
    // Keep angle in range [0, 2π]
    if (game->player->angle >= 2 * M_PI)
        game->player->angle -= 2 * M_PI;
}

void move_forward(t_game *game)
{
    double new_x;
    double new_y;
    double dir_x;
    double dir_y;
    
    // Calculate current direction from angle
    dir_x = cos(game->player->angle);
    dir_y = sin(game->player->angle);
    
    // Calculate new position
    new_x = game->player->pos_x + dir_x * MOVE_SPEED;
    new_y = game->player->pos_y + dir_y * MOVE_SPEED;
    
    // Collision detection
    if (game->maze->map[(int)new_y][(int)game->player->pos_x] != '1')
        game->player->pos_y = new_y;
    if (game->maze->map[(int)game->player->pos_y][(int)new_x] != '1')
        game->player->pos_x = new_x;
}

void move_backward(t_game *game)
{
    double new_x;
    double new_y;
    double dir_x;
    double dir_y;
    
    // Calculate current direction (same as forward)
    dir_x = cos(game->player->angle);
    dir_y = sin(game->player->angle);
    
    // Move in OPPOSITE direction (subtract instead of add)
    new_x = game->player->pos_x - dir_x * MOVE_SPEED;
    new_y = game->player->pos_y - dir_y * MOVE_SPEED;
    
    if (game->maze->map[(int)new_y][(int)game->player->pos_x] != '1')
        game->player->pos_y = new_y;
    if (game->maze->map[(int)game->player->pos_y][(int)new_x] != '1')
        game->player->pos_x = new_x;
}

//(move perpendicular to direction)
void move_left(t_game *game)
{
    double new_x;
    double new_y;
    double strafe_angle;
    
    // Left is 90° counterclockwise from current angle
    strafe_angle = game->player->angle - M_PI / 2;
    
    new_x = game->player->pos_x + cos(strafe_angle) * MOVE_SPEED;
    new_y = game->player->pos_y + sin(strafe_angle) * MOVE_SPEED;
    
    if (game->maze->map[(int)new_y][(int)game->player->pos_x] != '1')
        game->player->pos_y = new_y;
    if (game->maze->map[(int)game->player->pos_y][(int)new_x] != '1')
        game->player->pos_x = new_x;
}

void move_right(t_game *game)
{
    double new_x;
    double new_y;
    double strafe_angle;
    
    // Right is 90° clockwise from current angle
    strafe_angle = game->player->angle + M_PI / 2;
    
    new_x = game->player->pos_x + cos(strafe_angle) * MOVE_SPEED;
    new_y = game->player->pos_y + sin(strafe_angle) * MOVE_SPEED;
    
    if (game->maze->map[(int)new_y][(int)game->player->pos_x] != '1')
        game->player->pos_y = new_y;
    if (game->maze->map[(int)game->player->pos_y][(int)new_x] != '1')
        game->player->pos_x = new_x;
}

void mouse_move(int x, t_game *game)
{
    static int old_x = WIN_WIDTH / 2;
    double delta = (x - old_x) * 0.002;  // Mouse sensitivity
    
    game->player->angle += delta;  // Done!  
    
    old_x = x;
}