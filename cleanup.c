/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 04:55:02 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/28 04:55:04 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting/raycasting.h"

static void	free_texture_field(char **field)
{
	if (field && *field)
	{
		free(*field);
		*field = NULL;
	}
}

void	free_map(t_game *game)
{
	int	i;

	if (!game || !game->maze)
		return ;
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
		return ;
	free_texture_field(&game->texture->no);
	free_texture_field(&game->texture->so);
	free_texture_field(&game->texture->ea);
	free_texture_field(&game->texture->we);
	free_texture_field(&game->texture->c);
	free_texture_field(&game->texture->f);
	free(game->texture);
	game->texture = NULL;
}

void	cleanup(t_game *game)
{
	if (!game)
		return ;
	free_texture_paths(game);
	free_map(game);
	if (game->player)
	{
		free(game->player);
		game->player = NULL;
	}
}
