/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:30:00 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/22 11:30:02 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	map_mid_check_start(char **map, int y)
{
	if (map[y][0] == '*')
		return ;
	if (map[y][0] != '1' && map[y][0] != ' '
			&& map[y][0] != '\t')
	{
		printf("Error\n");
		printf("The map should be rounded by 1s !\n");
		printf("Failing row %d: '%s'\n", y, map[y]);
		exit(1);
	}
}

static void	map_mid_check_star(char **map, int y, int *px)
{
	int	j;
	int	x;

	x = *px;
	j = x - 1;
	while (j >= 0 && (map[y][j] == ' ' || map[y][j] == '\t'
			|| map[y][j] == '*'))
		j--;
	if (j < 0 || map[y][j] != '1')
	{
		printf("Error\n");
		printf("The map should be rounded by 1s !\n");
		printf("Failing row %d: '%s' (j=%d)\n", y, map[y], j);
		exit(1);
	}
	while (map[y][x] != '\0' && map[y][x] == '*')
		x++;
	if (map[y][x] != '\0' && map[y][x] != '*')
	{
		printf("Error\n");
		printf("Invalid character :/\n");
		exit(1);
	}
	*px = x;
}

static void	map_mid_check_end(char **map, int y, int x)
{
	if (map[y][x + 1] == '\0' && map[y][x] != '1'
			&& map[y][x] != '*' && map[y][x] != '\t'
			&& map[y][x] != ' ')
	{
		printf("Error\n");
		printf("The map should be rounded by 1s !\n");
		printf("Failing row %d: '%s'\n", y, map[y]);
		exit(1);
	}
}

void	check_map_mid(char **map)
{
	int	x;
	int	y;

	y = 1;
	while (map[y] != NULL)
	{
		if (map[y + 1] == NULL)
			break ;
		map_mid_check_start(map, y);
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
				check_zero(y, x, map);
			if (map[y][x] == '*')
			{
				map_mid_check_star(map, y, &x);
				break ;
			}
			map_mid_check_end(map, y, x);
			x++;
		}
		y++;
	}
}
