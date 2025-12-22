/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:10:00 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/22 12:10:02 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	fill_rest_with_stars(t_maze *maze, int y, int *px, int row)
{
	int	x;

	x = *px;
	while (x < row)
	{
		maze->map[y][x] = '*';
		x++;
	}
	*px = x;
}

static void	copy_line_to_row(t_maze *maze, int y, char *line, int row)
{
	int	x;

	x = 0;
	while (x < row)
	{
		if (line[x] == '\n' || line[x] == '\0')
		{
			fill_rest_with_stars(maze, y, &x, row);
			break ;
		}
		maze->map[y][x] = line[x];
		x++;
	}
	maze->map[y][row] = '\0';
}

static void	read_map_lines(t_maze *maze, int row, int column, int fd)
{
    char	*line;
    int		y;

    y = 0;
    line = get_next_line(fd);
    // NEW: skip header until first map line
    while (line && ft_strncmp(line, maze->first_line,
            ft_strlen(maze->first_line)) != 0)
    {
        free(line);
        line = get_next_line(fd);
    }
    while (line != NULL && y < column)
    {
        copy_line_to_row(maze, y, line, row);
        y++;
        free(line);
        line = get_next_line(fd);
    }
    if (line)
        free(line);
    maze->map[y] = NULL;
}

void	map_array(t_maze *maze, int row, int column, int fd)
{
	filling_struct_map(maze, row, column);
	read_map_lines(maze, row, column, fd);
}
