/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 08:53:56 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/22 08:53:58 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			break ;
		if ((line[i] >= 9 && line[i] <= 13) || line[i] == ' ')
			i++;
		else
			break ;
	}
	return (i);
}

static void	check_border_line(char *line, char *msg)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (line[x] == '1' || line[x] == ' ' || line[x] == '\t'
			|| line[x] == '*')
			x++;
		else
		{
			printf("Error\n");
			printf("%s\n", msg);
			exit(1);
		}
	}
}

void	check_first_nd_last_line(char **map, int last_column)
{
	check_stars(map, last_column);
	check_border_line(map[0],
		"First line should include just 1s and spaces !");
	check_border_line(map[last_column],
		"Last line should include just 1s and spaces !");
}

void	parse_space_error_msg(void)
{
	printf("Error\n");
	printf("Space should be rounded by 1s or spaces\n");
}

void	player_init(char **map, t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
				player_position(player, map[y][x], y, x);
			x++;
		}
		y++;
	}
	if (player->p == 'N')
		player->type = north;
	else if (player->p == 'S')
		player->type = south;
	else if (player->p == 'E')
		player->type = east;
	else if (player->p == 'W')
		player->type = west;
}
