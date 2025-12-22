/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:47:44 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/22 09:47:46 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	zero_error(int y, int x)
{
	printf("Error\n");
	printf("Invalid map: (0 in y-> %d and x-> %d "
		"should not be surrounded by spaces)\n",
		y, x);
	exit(1);
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

static void	check_star_line(char *line, char *msg)
{
	int	x;

	x = 0;
	while (line[x]
		&& (line[x] == '1' || line[x] == ' '
			|| line[x] == '\t'))
		x++;
	while (line[x] && line[x] == '*')
		x++;
	if (line[x])
	{
		printf("Error\n");
		printf("%s\n", msg);
		exit(1);
	}
}

void	check_stars(char **map, int last_column)
{
	check_star_line(map[0],
		"First line should include just 1s and spaces !");
	check_star_line(map[last_column],
		"Last line should include just 1s and spaces !");
}

void	check_zero(int y, int x, char **map)
{
	if (map[y - 1][x] == ' ' || map[y - 1][x] == '\t'
		|| map[y - 1][x] == '*' || map[y - 1][x] == '\0')
		zero_error(y, x);
	if (map[y + 1] != NULL
		&& (map[y + 1][x] == ' ' || map[y + 1][x] == '\t'
			|| map[y + 1][x] == '*' || map[y + 1][x] == '\0'))
		zero_error(y, x);
	if (map[y][x + 1] == ' ' || map[y][x + 1] == '\t'
		|| map[y][x + 1] == '*' || map[y][x + 1] == '\0')
		zero_error(y, x);
	if (map[y][x - 1] == ' ' || map[y][x - 1] == '\t'
		|| map[y][x - 1] == '*' || map[y][x - 1] == '\0')
		zero_error(y, x);
}
