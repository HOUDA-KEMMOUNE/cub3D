/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:35:42 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/22 09:35:44 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	player_position(t_player *player, char p, int y, int x)
{
	player->p = p;
	player->pos_x = (double)x + 0.5;
	player->pos_y = (double)y + 0.5;
}

void	parse_midle_space(t_maze *maze, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (skip_spaces_helper(map[y], &x) == 0)
				break ;
			if (map[y][x] == ' ' || map[y][x] == '\t')
			{
				parse_space(maze, map, x, y);
			}
			x++;
		}
		y++;
	}
}

void	print_map(t_maze *maze)
{
	int	y;

	y = 0;
	while (y < maze->column)
	{
		printf("%s\n", maze->map[y]);
		y++;
	}
}

void	map_filling(t_maze *maze, int fd, char *file)
{
	char	*line;
	int		row;
	int		column;

	line = get_next_line(fd);
	while (line != NULL && ft_strncmp(line, maze->first_line,
			ft_strlen(maze->first_line)) != 0)
	{
		free(line);
		line = get_next_line(fd);
	}
	maze_max_row(maze, fd, line);
	row = maze->max_row;
	column = maze->column;
	close (fd);
	fd = open(file, O_RDONLY);
	map_array(maze, row, column, fd);
}

void	filling_struct_map(t_maze *maze, int row, int column)
{
	int	y;

	maze->map = ft_calloc(column + 1, sizeof(char *));
	y = 0;
	while (y < column)
	{
		maze->map[y] = ft_calloc(row + 1, sizeof(char));
		y++;
	}
	maze->map[column] = NULL;
}
