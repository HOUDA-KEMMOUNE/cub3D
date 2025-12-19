#include "raycasting.h"

// Check if MLX allocation succeeded
static void	check_arg(void *ptr)
{
	if (ptr == NULL)
	{
		printf("Error\nMLX initialization failed\n");
		exit(1);
	}
}
// Close window and clean up resources
int	close_window(t_game *game)
{
	if (game->mlx.img. img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.img.img);
	if (game->mlx.win)
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	if (game->mlx.mlx)
	{
		mlx_destroy_display(game->mlx.mlx);
		free(game->mlx.mlx);
	}
	exit(0);
	return (0);
}

// Handle key press events
int	key_press(int key_code, t_game *game)
{
	if (key_code == KEY_ESC)
		close_window(game);
	else if (key_code == KEY_W)
		move_forward(game);
	else if (key_code == KEY_S)
		move_backward(game);
	else if (key_code == KEY_A)
		move_left(game);
	else if (key_code == KEY_D)
		move_right(game);
	else if (key_code == KEY_LEFT)
		rotate_left(game);
	else if (key_code == KEY_RIGHT)
		rotate_right(game);
	return (0);
}

// Loop hook - called every frame
static int	loop_hook(t_game *game)
{
	render_frame(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, 
		game->mlx.img.img, 0, 0);
	return (0);
}

// Initialize and start the game
void	start_cub3D(t_game *game)
{
	// Initialize MLX
	game->mlx.mlx = mlx_init();
	check_arg(game->mlx.mlx);
	
	// Create window
	game->mlx. win = mlx_new_window(game->mlx.mlx, WIN_WIDTH, 
		WIN_HEIGHT, "cub3D");
	check_arg(game->mlx.win);
	
	// Create image buffer
	game->mlx.img.img = mlx_new_image(game->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	check_arg(game->mlx.img. img);
	
	// Get image data address
	game->mlx.img.addr = mlx_get_data_addr(game->mlx.img.img, 
		&game->mlx. img.bpp, &game->mlx. img.line_lenght, &game->mlx.img.endian);
	
	// Initialize player direction based on spawn orientation
	init_player_direction(game->player);
	
	// Set up event hooks
	mlx_hook(game->mlx.win, 17, 0, close_window, game);          // X button
	mlx_hook(game->mlx.win, 2, 1L << 0, key_press, game);        // Key press
	mlx_loop_hook(game->mlx. mlx, loop_hook, game);               // Render loop
	
	// Start the MLX loop
	mlx_loop(game->mlx.mlx);
}