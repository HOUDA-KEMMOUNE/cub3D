/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:30:00 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/22 10:30:02 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
			if (map[y][x] == ' ' || map[y][x] == '\t' || map[y][x] == '*'
				|| map[y][x] == '1' || map[y][x] == '0'
				|| map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
				x++;
			else
			{
				printf("Error\n");
				printf("Invalid character in the map :/\n");
				exit(1);
			}
		}
		y++;
	}
}
