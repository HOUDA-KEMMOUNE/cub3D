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

int	check_line(char *line)
{
	if (line[0] == '1' || line[0] == ' ')
		return (1);
	return (0);
}

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

int	check_first_line(char *line)
{
	int	i;

	i = 0;
	
	i = skip_spaces(line);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1')
		{
			printf("The first line in the map should contain just 1\n");
			exit(1);
		}
		i++;
	}
	return (0);
}

int	check_map_mid(char *line)
{
	int	i;
	int	v;

	i = 0;
	v = 0;
	i = skip_spaces(line);
	if (line[i] == '\0' || line[i] == '\n')
    {
        printf("Invalid empty map line\n");
        exit(1);
    }
	while (line[i])
	{
		if (line[i] == '\n')
			break;
		if (line[i + 1] == '\n')
		{
			if (line[i] != '1')
			{
				printf("The maze should be rounded with 1s\n");
				free (line);
				exit(1);

			}
		}
		if (line[i] != '1' && v == 0)
		{
			if (line[i] != 1)
			{
				printf("The maze should be rounded with 1s\n");
				free (line);
				exit(1);
			}
		}
		i++;
		v++;
	}
	return (1);
}

int	count_map_lines(int fd)
{
	int		count;
	char	*line;

	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (check_map_mid(line) == 1)
		{
			count++;
		}
		free (line);
		line = get_next_line(fd);
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
	//printf("line --> %s\n", line);
	while (line != NULL)
	{
		while (line[i] != '\n')
		{
			if (line[i] == '\0')
				break ;
			if (!((line[i] >= 9 && line[i] <= 13) || line[i] == ' '))
				count++;
			i++;
		}
		if (max < count)
			max = count;
		//printf("max --> %d\n", max);
		//printf("count --> %d\n", count);
		//printf("line --> %s\n", line);
		count = 0;
		i = 0;
		line = get_next_line(fd);
	}
	maze->max_row = max;
}

void	map_filling(t_maze *maze, int fd)
{
	char	*line;

	//line = maze->first_line;
	line = get_next_line(fd);
	while ((line != NULL) && (ft_strncmp(line, maze->first_line, ft_strlen(maze->first_line) != 0)))
	{
		line = get_next_line(fd);
	}
	maze_max_row(maze, fd, line);
	printf("maze->max_row --> %d\n", maze->max_row);
}

int	map_parsing(char *file_name)
{
	int		fd;
	//int		fd_copy;
	char	*line;
	// char	*copy_line;
	// int		count;
	t_maze	*maze;

	fd = open(file_name, O_RDONLY);
	//fd_copy = fd;
	maze = malloc(sizeof(t_maze));
	maze_init(maze);
	if (fd < 0)
	{
		printf("File doesn't exist :/\n");
		exit (1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (check_line(line) == 1)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	check_first_line(line);
	maze->first_line = line;
	maze->count = 1 + count_map_lines(fd);
	close(fd);
	//print_maze_struct(maze);
	fd = open(file_name, O_RDONLY);

	map_filling(maze, fd);
	free(line);
	//close(fd);
	return (100);
}
