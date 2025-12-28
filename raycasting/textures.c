/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 04:45:38 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/28 04:45:40 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void	load_single_texture(t_mlx *mlx, t_wall_tex *tex, char *path)
{
	int	width;
	int	height;

	if (!path)
	{
		printf("Error\nMissing texture path\n");
		exit(1);
	}
	tex->img = mlx_xpm_file_to_image(mlx->mlx, path, &width, &height);
	if (!tex->img)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		exit(1);
	}
	tex->width = width;
	tex->height = height;
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_lenght, &tex->endian);
	if (!tex->addr)
	{
		printf("Error\nFailed to get texture data: %s\n", path);
		exit(1);
	}
}

void	load_textures(t_game *game)
{
	if (!game->texture)
	{
		printf("Error\nTexture struct not initialized\n");
		exit(1);
	}
	load_single_texture(&game->mlx, &game->north_tex, game->texture->no);
	load_single_texture(&game->mlx, &game->south_tex, game->texture->so);
	load_single_texture(&game->mlx, &game->west_tex, game->texture->we);
	load_single_texture(&game->mlx, &game->east_tex, game->texture->ea);
}
