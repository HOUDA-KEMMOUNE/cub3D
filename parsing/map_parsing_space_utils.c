/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_space_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:25:00 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/22 13:25:02 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_border_space(t_maze *maze, char **map, int x, int y)
{
	if (y != 0 && y != maze->column - 1)
		return (0);
	if (x != 0 && map[y][x + 1] != '\0')
		return (0);
	if (map[y - 1][x] != ' ' && map[y - 1][x] != '\t'
		&& map[y - 1][x] != '1')
	{
		parse_space_error_msg();
		exit(1);
	}
	return (1);
}
