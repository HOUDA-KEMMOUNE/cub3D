/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:05:00 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/22 13:05:02 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	count_player_chars(char **map, int counts[4])
{
	int	x;
	int	y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N')
				counts[0] = 1;
			else if (map[y][x] == 'S')
				counts[1] = 1;
			else if (map[y][x] == 'E')
				counts[2] = 1;
			else if (map[y][x] == 'W')
				counts[3] = 1;
			x++;
		}
		y++;
	}
}

void	check_player(char **map, int x, int y)
{
	int	counts[4];

	(void)x;
	(void)y;
	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	counts[3] = 0;
	count_player_chars(map, counts);
	if (counts[0] == 0 && counts[1] == 0
		&& counts[2] == 0 && counts[3] == 0)
	{
		printf("Error\n");
		printf("Where is the player ?!\n");
		exit(1);
	}
}
