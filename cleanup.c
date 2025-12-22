#include "raycasting/raycasting.h"

void	free_map(t_game *game)
{
	int	i;

	if (!game || !game->maze)
		return;
	
	if (game->maze->map)
	{
		i = 0;
		while (i < game->maze->max_row && game->maze->map[i])
		{
			free(game->maze->map[i]);
			game->maze->map[i] = NULL;
			i++;
		}
		free(game->maze->map);
		game->maze->map = NULL;
	}
	
	free(game->maze);
	game->maze = NULL;
}

void	free_texture_paths(t_game *game)
{
	if (!game || !game->texture)
		return;
	
	if (game->texture->no)
	{
		free(game->texture->no);
		game->texture->no = NULL;
	}
	if (game->texture->so)
	{
		free(game->texture->so);
		game->texture->so = NULL;
	}
	if (game->texture->ea)
	{
		free(game->texture->ea);
		game->texture->ea = NULL;
	}
	if (game->texture->we)
	{
		free(game->texture->we);
		game->texture->we = NULL;
	}
	if (game->texture->c)
	{
		free(game->texture->c);
		game->texture->c = NULL;
	}
	if (game->texture->f)
	{
		free(game->texture->f);
		game->texture->f = NULL;
	}
	
	free(game->texture);
	game->texture = NULL;
}

// Main cleanup function
void	cleanup(t_game *game)
{
	if (!game)
		return;
	free_texture_paths(game);
	free_map(game);
	if (game->player)
	{
		free(game->player);
		game->player = NULL;
	}
}