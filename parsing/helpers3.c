/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:40:21 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/22 09:40:23 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	multi_player_error(void)
{
	printf("Error\n");
	printf("Just one player should be spawned in the map !\n");
	exit(1);
}

void	check_multi_player(t_flags spawn_char)
{
	if (spawn_char.e > 1 || spawn_char.s > 1
		|| spawn_char.n > 1 || spawn_char.w > 1)
		multi_player_error();
	if (spawn_char.s == 1
		&& (spawn_char.e == 1 || spawn_char.n == 1 || spawn_char.w == 1))
		multi_player_error();
	if (spawn_char.n == 1
		&& (spawn_char.s == 1 || spawn_char.e == 1 || spawn_char.w == 1))
		multi_player_error();
	if (spawn_char.w == 1
		&& (spawn_char.s == 1 || spawn_char.n == 1 || spawn_char.e == 1))
		multi_player_error();
}

int	count_map_lines(int fd)
{
	int		count;
	char	*line;

	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		count++;
	}
	return (count);
}

static void	count_spawn_chars(char **map, t_flags *spawn_char)
{
	int	x;
	int	y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'N')
				spawn_char->n++;
			else if (map[y][x] == 'S')
				spawn_char->s++;
			else if (map[y][x] == 'E')
				spawn_char->e++;
			else if (map[y][x] == 'W')
				spawn_char->w++;
			x++;
		}
		y++;
	}
}

void	spawn_check(t_maze *maze, char **map)
{
	t_flags	spawn_char;

	(void)maze;
	flags_init(&spawn_char);
	invalid_character(map);
	count_spawn_chars(map, &spawn_char);
	check_multi_player(spawn_char);
}
