/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:38:51 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/10/16 16:38:54 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parsing.h"

int	main(void)
{
	int	fd;

	fd = open("map.cub", O_RDONLY);
	if (fd < 0)
	{
		printf("Not a valid file :/\n");
		return (1);
	}
	if (parsing_directions(fd) == 1)
	{
		close(fd);
		exit (1);
	}
	close (fd);
	if (parse_fc_color("map.cub") == 0)
		exit (1);
	map_parsing("map.cub");
	
}
