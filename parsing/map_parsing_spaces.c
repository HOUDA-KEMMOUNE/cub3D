/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_spaces.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:40:00 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/22 12:40:02 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	parse_space_neighbors(char **map, int x, int y)
{
	if (map[y + 1] != NULL && map[y + 1][x] != ' '
		&& map[y + 1][x] != '\t' && map[y + 1][x] != '1')
	{
		parse_space_error_msg();
		exit(1);
	}
	if (map[y][x + 1] != '\0' && map[y][x + 1] != ' '
		&& map[y][x + 1] != '\t' && map[y][x + 1] != '1')
	{
		parse_space_error_msg();
		exit(1);
	}
	if (map[y][x - 1] != ' ' && map[y][x - 1] != '\t'
		&& map[y][x - 1] != '1')
	{
		parse_space_error_msg();
		exit(1);
	}
}

static void	parse_space_diag_down(char **map, int x, int y)
{
	if (map[y + 1] != NULL && map[y + 1][x + 1] != '\0'
		&& map[y + 1][x + 1] != ' ' && map[y + 1][x + 1] != '\t'
		&& map[y + 1][x + 1] != '1')
	{
		parse_space_error_msg();
		exit(1);
	}
	if (map[y + 1] != NULL && map[y + 1][x - 1] != ' '
		&& map[y + 1][x - 1] != '\t' && map[y + 1][x - 1] != '1')
	{
		parse_space_error_msg();
		exit(1);
	}
}

static void	parse_space_diag_up(char **map, int x, int y)
{
	if (map[y - 1][x + 1] != '\0'
		&& map[y - 1][x + 1] != ' ' && map[y - 1][x + 1] != '\t'
		&& map[y - 1][x + 1] != '1')
	{
		parse_space_error_msg();
		exit(1);
	}
	if (map[y - 1][x - 1] != ' ' && map[y - 1][x - 1] != '\t'
		&& map[y - 1][x - 1] != '1')
	{
		parse_space_error_msg();
		exit(1);
	}
}

static void	parse_space_diagonals(char **map, int x, int y)
{
	parse_space_diag_down(map, x, y);
	parse_space_diag_up(map, x, y);
}

void	parse_space(t_maze *maze, char **map, int cx, int cy)
{
	if (!is_border_space(maze, map, cx, cy))
		return ;
	parse_space_neighbors(map, cx, cy);
	parse_space_diagonals(map, cx, cy);
}
