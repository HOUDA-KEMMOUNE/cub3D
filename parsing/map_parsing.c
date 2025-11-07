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

void	check_line(char *file_name)
{
	int		fd;
	int		i;
	int		flag;
	char	*line;

	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strnstr(line, "111", ft_strlen(line)) != NULL)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	while (line != NULL)
	{
		i = 0;
		flag = 0;
		printf("line --> %s\n", line);
		while (line[i])
		{
			if (line[i] == ' ' || line[i] == '\t')
				i++;
			else
			{
				// printf("re\n");
				flag = 1;
				i++;
			}
		}
		if (line[i] == '\0' && flag == 0)
		{
			printf("Error\n");
			printf("Empty line :/\n");
			exit (1);
		}
		line = get_next_line(fd);                                                                                               
	}
}

// void	check_line(char **map)
// {

// }

int	skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			break;
		if ((line[i] >= 9 && line[i] <= 13) || line[i] == ' ')
			i++;
		else
			break ;
	}
	return (i);
}

void	check_stars(char **map, int last_column)
{
	int	x;

	x = 0;
	while ((map[0][x]) && (map[0][x] == '1' || map[0][x] == ' ' || map[0][x] == '\t'))
	{
		x++;
	}
	while ((map[0][x]) && (map[0][x] == '*'))
		x++;
	if (map[0][x])
	{
		printf("Error\n");
		printf("First line should include just 1s and spaces !\n");
		exit (1);
	}
	x = 0;
	while ((map[last_column][x]) && (map[last_column][x] == '1' || map[last_column][x] == ' ' || map[last_column][x] == '\t'))
	{
		x++;
	}
	while ((map[last_column][x]) && (map[last_column][x] == '*'))
		x++;
	if (map[last_column][x])
	{
		printf("Error\n");
		printf("Last line should include just 1s and spaces !\n");
		exit (1);
	}
}

void	check_first_nd_last_line(char **map, int last_column)
{
	int	x;
	// --------------- First line ------------------
	x = 0;
	check_stars(map, last_column);
	while (map[0][x])
	{
		if (map[0][x] == '1' || map[0][x] == ' ' || map[0][x] == '\t' || map[0][x] == '*')
			x++;
		else
		{
			printf("Error\n");
			printf("First line should include just 1s and spaces !\n");
			exit (1);
		}
	}
	x = 0;
	while (map[last_column][x])
	{
		if (map[last_column][x] == '1' || map[last_column][x] == ' ' || map[last_column][x] == '\t' || map[last_column][x] == '*')
			x++;
		else
		{
			printf("Error\n");
			printf("Last line should include just 1s and spaces !\n");
			exit (1);
		}
	}
}

// void	check_empty_line(char **map)
// {
// 	int	x;
// 	int	y;
// 	int	end_line;

// 	y = 0;
// 	end_line = 0;
// 	while (map[y] != NULL)
// 	{
// 		x = 0;
// 		while (map[y][x])
// 		{
// 			if (map[y][x] == ' ' || map[y][x] == '\t' || map[y][x] == '1' || map[y][x] == '*')
// 				end_line = 1;
// 			else
// 			{
// 				end_line = 0;
// 				break ;
// 			}
// 			x++;
// 		}
// 		if (end_line == 1)
// 		{
// 			while (map[y] != NULL)
// 			{
// 				x = 0;
// 				if (map[y][x] != '*')
// 				{
// 					printf("Error\n");
// 					printf("Invalid map (check_wmpty_line)\n");
// 					exit (1);
// 				}
// 				x++;
// 			}
// 			y++;
// 		}
// 		y++;
// 	}
// }

void	check_zero(int y, int x, char **map)
{
	if (map[y - 1][x] == ' ' || map[y - 1][x] == '\t' || map[y - 1][x] == '*' || map[y - 1][x] == '\0')
	{
		printf("Error\n");
		printf("Invalid map: (0 in y-> %d and x-> %d should not be surrounded by spaces)\n", y, x);
		exit (1);
	}
	if ((map[y + 1] != NULL) && (map[y + 1][x] == ' ' || map[y + 1][x] == '\t' || map[y + 1][x] == '*' || map[y + 1][x] == '\0'))
	{
		printf("Error\n");
		printf("Invalid map: (0 in y-> %d and x-> %d should not be surrounded by spaces)\n", y, x);
		exit (1);
	}
	if (map[y][x + 1] == ' ' || map[y][x + 1] == '\t' || map[y][x + 1] == '*' || map[y][x + 1] == '\0')
	{
		printf("Error\n");
		printf("Invalid map: (0 in y-> %d and x-> %d should not be surrounded by spaces)\n", y, x);
		exit (1);
	}
	if (map[y][x - 1] == ' ' || map[y][x - 1] == '\t' || map[y][x - 1] == '*' || map[y][x - 1] == '\0')
	{
		printf("Error\n");
		printf("Invalid map: (0 in y-> %d and x-> %d should not be surrounded by spaces)\n", y, x);
		exit (1);
	}
}

void	check_map_mid(char **map)
{
	int	x;
	int	y;
	int	j;

	y = 1;
	while (map[y] != NULL)
	{
		if (map[y + 1] == NULL)
			break ;
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
				check_zero(y, x, map);
			if (map[y][0] == '*')
				break ;
			if (map[y][0] != '1' && map[y][0] != ' ' && map[y][0] != '\t')
			{
				printf("Error\n");
				printf("The map should be rounded by 1s !\n");
				printf("Failing row %d: '%s'\n", y, map[y]);
				exit (1);
			}
			if (map[y][x] == '*')
			{
				j = x - 1;
				while (j >= 0 && (map[y][j] == ' ' || map[y][j] == '\t' || map[y][j] == '*'))
					j--;
				if (j < 0 || map[y][j] != '1')
				{
					printf("Error\n");
					printf("The map should be rounded by 1s !\n");
					printf("Failing row %d: '%s' (j=%d)\n", y, map[y], j);
					exit (1);
				}
				if (map[y][x] != '\0' && map[y][x] == '*')
				{
					while (map[y][x] != '\0' && map[y][x] == '*')
						x++;
					if (map[y][x] != '\0' && map[y][x] != '*')
					{
						printf("Error\n");
						printf("Invalid character :/\n");
						exit (1);
					}
				}
				break ;
			}
				if ((map[y][x + 1] == '\0') && (map[y][x] != '1' && map[y][x] != '*' && map[y][x] != '\t' && map[y][x] != ' '))
				{
					printf("Error\n");
					printf("The map should be rounded by 1s !\n");
					printf("Failing row %d: '%s'\n", y, map[y]);
					exit (1);
				}
			x++;
		}
		y++;
	}
}
/*
int	count_map_lines(int fd)
{
	int		count;
	int		i;
	char	*line;

	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (skip_spaces(line) >= 0)
		{
			i = skip_spaces(line);
			if (line[i] == '\0' || line[i] == '\n')
			{
				free(line);
				break;
			}
		}
		count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}
*/

int	count_map_lines(int fd)
{
	int		count;
	//int		i;
	char	*line;

	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		//printf("line (count_map_lines) --> %s\n", line);
		free (line);
		line = get_next_line(fd);
		count++;
	}
	return (count);
}

void	maze_max_row(t_maze *maze, int fd, char *line)
{
	int	max;
	int	count;
	int	i;

	max = 0;
	count = 0;
	i = 0;
	while (line != NULL)
	{
		while (line[i] != '\n')
		{
			if (line[i] == '\0')
				break ;
			count++;
			i++;
		}
		if (max < count)
			max = count;
		count = 0;
		i = 0;
		free(line);
		line = get_next_line(fd);
	}
	maze->max_row = max;
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
}

void	map_array(t_maze *maze, int row, int column, int fd)
{
	char	*line;
	int		x;
	int		y;

	filling_struct_map(maze, row, column);
	line = get_next_line(fd);
	while (line != NULL && ft_strncmp(line, maze->first_line, ft_strlen(maze->first_line)) != 0)
	{
		free(line);
		line = get_next_line(fd);
	}
    y = 0;
    while (line != NULL && y < column)
    {
        x = 0;
        while (x < row)
        {
            if (line[x] == '\n' || line[x] == '\0')
            {
                while (x < row)
                {
                    maze->map[y][x] = '*';
                    x++;
                }
                break ;
            }
            maze->map[y][x] = line[x];
            x++;
        }
        maze->map[y][row] = '\0';
		y++;
		free(line);
		line = get_next_line(fd);
    }
	if (line)
		free(line);
	maze->map[y] = NULL;
}

void	map_filling(t_maze *maze, int fd, char *file)
{
	char	*line;
	int		row;
	int		column;

	line = get_next_line(fd);
	while (line != NULL && ft_strncmp(line, maze->first_line, ft_strlen(maze->first_line)) != 0)
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

static void free_maze(t_maze *maze)
{
	int i;

	if (!maze)
		return;
	if (maze->first_line)
		free(maze->first_line);
	if (maze->map)
	{
		i = 0;
		while (maze->map[i])
		{
			free(maze->map[i]);
			i++;
		}
		free(maze->map);
	}
	free(maze);
}

void	print_map(t_maze *maze)
{
	int	y = 0;
	while (y < maze->column)
	{
		printf("%s\n", maze->map[y]);
		y++;
	}
}

void	invalid_character(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == ' ' || map[y][x] == '\t' || map[y][x] == '*' || map[y][x] == '1'
			   || map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S'
			   || map[y][x] == 'E' || map[y][x] == 'W')
				x++;
			else
			{
				printf("Error\n");
				printf("Invalid character in the map :/\n");
				exit (1);
			}
		}
		y++;
	}
}

void	check_multi_player(t_flags spawn_char)
{
	if (spawn_char.e > 1 || spawn_char.s > 1 || spawn_char.n > 1 || spawn_char.w > 1)
	{
		printf("Error\n");
		printf("Just one player should be spawned in the map !\n");
		exit (1);
	}
	if ((spawn_char.s == 1) && (spawn_char.e == 1 || spawn_char.n == 1 || spawn_char.w == 1))
	{
		printf("Error\n");
		printf("Just one player should be spawned in the map !\n");
		exit (1);
	}
	if ((spawn_char.n == 1) && (spawn_char.s == 1 || spawn_char.e == 1 || spawn_char.w == 1))
	{
		printf("Error\n");
		printf("Just one player should be spawned in the map !\n");
		exit (1);
	}
	if ((spawn_char.w == 1) && (spawn_char.s == 1 || spawn_char.n == 1 || spawn_char.e == 1))
	{
		printf("Error\n");
		printf("Just one player should be spawned in the map !\n");
		exit (1);
	}
}

void	spawn_check(t_maze *maze, char **map)
{
	// N,S,E or W
	(void)maze;
	int		x;
	int		y;
	t_flags	spawn_char;

	flags_init(&spawn_char);
	y = 0;
	invalid_character(map);
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'N')
				spawn_char.n++;
			else if (map[y][x] == 'S')
				spawn_char.s++;
			else if (map[y][x] == 'E')
				spawn_char.e++;
			else if (map[y][x] == 'W')
				spawn_char.n++;
			x++;
		}
		y++;
	}
	check_multi_player(spawn_char);
}

void	parse_space_error_msg(void)
{
	printf("Error\n");
	printf("Space should be rounded by 1s or spaces\n");
}

void	parse_space(t_maze *maze, char **map, int cx, int cy)
{
	int	x;
	int	y;

	// touch parse_space_cases ondir l cases on3ayat 3lihom hna
	x = cx;
	y = cy;
	if (y != 0 && y != maze->column - 1)
		return ;
	if (x != 0 && map[y][x + 1] != '\0')
		return ;
	if (map[y - 1][x] != ' ' && map[y - 1][x] != '\t' && map[y - 1][x] != '1')
	{
		// printf("1\n");
		parse_space_error_msg();
		exit (1);
	}
	if ((map[y + 1] != NULL) && (map[y + 1][x] != ' ' && map[y + 1][x] != '\t' && map[y + 1][x] != '1'))
	{
		// printf("2\n");
		parse_space_error_msg();
		exit (1);
	}
	if ((map[y][x + 1] != '\0') && (map[y][x + 1] != ' ' && map[y][x + 1] != '\t' && map[y][x + 1] != '1'))
	{
		// printf("3\n");
		parse_space_error_msg();
		exit (1);
	}
	if (map[y][x - 1] != ' ' && map[y][x - 1] != '\t' && map[y][x - 1] != '1')
	{
		// printf("4\n");
		parse_space_error_msg();
		exit (1);
	}
	if ((map[y + 1] != NULL) && (map[y + 1][x + 1] != '\0') && (map[y + 1][x + 1] != ' ' && map[y + 1][x + 1] != '\t' && map[y + 1][x + 1] != '1'))
	{
		// printf("5\n");
		parse_space_error_msg();
		exit (1);
	}
	if ((map[y + 1] != NULL) && (map[y + 1][x - 1] != ' ' && map[y + 1][x - 1] != '\t' && map[y + 1][x - 1] != '1'))
	{
		// printf("6\n");
		parse_space_error_msg();
		exit (1);
	}
	if ((map[y - 1][x + 1] != '\0') && (map[y - 1][x + 1] != ' ' && map[y - 1][x + 1] != '\t' && map[y - 1][x + 1] != '1'))
	{
		// printf("7\n");
		parse_space_error_msg();
		exit (1);
	}
	if (map[y - 1][x - 1] != ' ' && map[y - 1][x - 1] != '\t' && map[y - 1][x - 1] != '1')
	{
		// printf("8\n");
		parse_space_error_msg();
		exit (1);
	}
}

void	parse_midle_space(t_maze * maze, char **map)
{
	int	x;
	int	y;

	// map = maze->map;
	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (skip_spaces_helper(map[y], &x) == 0)
				break;
			if (map[y][x] == ' ' || map[y][x] == '\t')
			{
				parse_space(maze, map, x, y);
			}
			x++;
		}
		y++;
	}
}

void	check_player(char **map, int x, int y)
{
	//N,S,E or W 
	int	n;
	int	s;
	int	e;
	int	w;

	n = 0;
	s = 0;
	e = 0;
	w = 0;
	while (map[y]!= NULL)
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N')
				n = 1;
			else if (map[y][x] == 'S')
				s = 1;
			else if (map[y][x] == 'E')
				e = 1;
			else if (map[y][x] == 'W')
				w = 1;
			x++;
		}
		y++;
	}
	if (n == 0 && s == 0 && e == 0 && w == 0)
	{
		printf("Error\n");
		printf("Where is the player ?!\n");
		exit (1);
	}
}

int	map_parsing(char *file_name)
{
	int		fd;
	char	*line;
	t_maze	*maze;

	fd = open(file_name, O_RDONLY);
	maze = malloc(sizeof(t_maze));
	maze_init(maze);
	if (fd < 0)
	{
		printf("Error\n");
		printf("File doesn't exist :/\n");
		exit (1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strnstr(line, "111", ft_strlen(line)) != NULL)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	// check_line(file_name);
	maze->first_line = line;
	maze->column = 1 + count_map_lines(fd);
	close(fd);
	fd = open(file_name, O_RDONLY);
	map_filling(maze, fd, file_name);
	// print_map(maze);
	check_player(maze->map, 0, 0);
	check_first_nd_last_line(maze->map, maze->column - 1);
	check_map_mid(maze->map);
	spawn_check(maze, maze->map);
	parse_midle_space(maze, maze->map);
	printf("Valid map ✅\n");
	free_maze(maze);
	return (100);
}
