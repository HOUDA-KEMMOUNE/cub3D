/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      :::: ::::   */
/*   cleanup. c                                          :+:      :+:    :+:   */
/*                                                    +: + +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 12:00:00 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/28 12:00:02 by hkemmoun         ###   ########. fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting/raycasting.h"

static void	safe_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_map(t_game *game)
{
	int	i;

	if (!game || !game->maze)
		return;
	
	if (game->maze->map)
	{
		i = 0;
		while (game->maze->map[i] != NULL)
		{
			safe_free((void **)&game->maze->map[i]);
			i++;
		}
		safe_free((void **)&game->maze->map);
	}
	safe_free((void **)&game->maze->first_line);
	safe_free((void **)&game->maze);
}

void	free_texture_paths(t_game *game)
{
	if (!game || !game->texture)
		return;
	
	safe_free((void **)&game->texture->no);
	safe_free((void **)&game->texture->so);
	safe_free((void **)&game->texture->ea);
	safe_free((void **)&game->texture->we);
	safe_free((void **)&game->texture->c);
	safe_free((void **)&game->texture->f);
	
	safe_free((void **)&game->texture);
}

void	cleanup(t_game *game)
{
	if (! game)
		return;
	free_texture_paths(game);
	free_map(game);
	safe_free((void **)&game->player);
}