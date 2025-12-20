#include "raycasting.h"

static void	check_arg(void *ptr)
{
	if (ptr == NULL)
	{
		printf("Error\nMLX initialization failed\n");
		exit(1);
	}
}

int	close_window(t_game *game)
{
	if (game->mlx.img.img)
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

int	key_press(int key_code, t_game *game)
{
	if (key_code == KEY_ESC)
		game->keys.esc = 1;
	else if (key_code == KEY_W)
		game->keys.w = 1;
	else if (key_code == KEY_S)
		game->keys.s = 1;
	else if (key_code == KEY_A)
		game->keys.a = 1;
	else if (key_code == KEY_D)
		game->keys.d = 1;
	else if (key_code == KEY_LEFT)
		game->keys.left = 1;
	else if (key_code == KEY_RIGHT)
		game->keys.right = 1;
	return (0);
}

int	key_release(int key_code, t_game *game)
{
	if (key_code == KEY_ESC)
		game->keys.esc = 0;
	else if (key_code == KEY_W)
		game->keys.w = 0;
	else if (key_code == KEY_S)
		game->keys.s = 0;
	else if (key_code == KEY_A)
		game->keys.a = 0;
	else if (key_code == KEY_D)
		game->keys.d = 0;
	else if (key_code == KEY_LEFT)
		game->keys.left = 0;
	else if (key_code == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}

// 🆕 Get current time in milliseconds
long	get_time_ms(void)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// 🆕 Calculate delta time (time since last frame)
void	calculate_delta_time(t_game *game)
{
	long	current_time;
	
	current_time = get_time_ms();
	
	// Delta time in seconds (convert milliseconds to seconds)
	game->delta_time = (current_time - game->last_time) / 1000.0;
	
	// Cap delta time to prevent huge jumps
	// (happens if window is dragged, computer hiccups, etc.)
	if (game->delta_time > 0.05)  // Max 50ms = minimum 20 FPS
		game->delta_time = 0.05;
	
	// Prevent zero or negative delta time
	if (game->delta_time <= 0.0)
		game->delta_time = 0.016;  // Default to ~60 FPS
	
	game->last_time = current_time;
}

void	handle_movement(t_game *game)
{
	if (game->keys. esc)
		close_window(game);
	
	if (game->keys.w)
		move_forward(game);
	if (game->keys.s)
		move_backward(game);
	if (game->keys.a)
		move_left(game);
	if (game->keys.d)
		move_right(game);
	
	if (game->keys.left)
		rotate_left(game);
	if (game->keys.right)
		rotate_right(game);
}

// 🆕 Loop hook with delta time calculation
static int	loop_hook(t_game *game)
{
	// Calculate time since last frame
	calculate_delta_time(game);
	
	// Process input (movement now uses delta_time)
	handle_movement(game);
	
	// Render
	render_frame(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, 
		game->mlx.img.img, 0, 0);
	
	return (0);
}

void	start_cub3D(t_game *game)
{
	// Initialize key states
	game->keys.w = 0;
	game->keys.s = 0;
	game->keys.a = 0;
	game->keys. d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	game->keys. esc = 0;
	
	// 🆕 Initialize timing
	game->last_time = get_time_ms();
	game->delta_time = 0.016;  // Start with ~60 FPS assumption
	
	// Initialize MLX
	game->mlx. mlx = mlx_init();
	check_arg(game->mlx.mlx);
	
	game->mlx.win = mlx_new_window(game->mlx.mlx, WIN_WIDTH, 
		WIN_HEIGHT, "cub3D");
	check_arg(game->mlx.win);
	
	game->mlx.img.img = mlx_new_image(game->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	check_arg(game->mlx.img. img);
	
	game->mlx.img.addr = mlx_get_data_addr(game->mlx.img.img, 
		&game->mlx. img.bpp, &game->mlx.img.line_lenght, &game->mlx. img.endian);
	
	init_player_direction(game->player);
	
	mlx_hook(game->mlx.win, 17, 0, close_window, game);
	mlx_hook(game->mlx.win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx.win, 3, 1L << 1, key_release, game);
	mlx_loop_hook(game->mlx.mlx, loop_hook, game);
	
	mlx_loop(game->mlx.mlx);
}
