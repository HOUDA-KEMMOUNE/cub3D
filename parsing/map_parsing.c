/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 23:44:20 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/10/19 23:44:21 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	open_map_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\n");
		printf("File doesn't exist :/\n");
		exit(1);
	}
	return (fd);
}

static char	*find_first_map_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strnstr(line, "111", ft_strlen(line)) != NULL)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

void	map_parsing(char *file_name, t_maze *maze, t_player *player)
{
	int		fd;
	char	*line;

	maze_init(maze);
	fd = open_map_file(file_name);
	line = find_first_map_line(fd);
	maze->first_line = line;
	maze->column = 1 + count_map_lines(fd);
	close(fd);
	fd = open_map_file(file_name);
	map_filling(maze, fd, file_name);
	check_player(maze->map, 0, 0);
	check_first_nd_last_line(maze->map, maze->column - 1);
	check_map_mid(maze->map);
	spawn_check(maze, maze->map);
	parse_midle_space(maze, maze->map);
	player_init(maze->map, player);
	printf("Valid map ✅\n");
}
