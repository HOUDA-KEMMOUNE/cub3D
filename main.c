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
		printf("Error\n");
		printf("Not a valid file :/\n");
		return (1);
	}
	if (parsing_directions(fd) == 1)
	{
		close(fd);
		exit (1);
	}
	/* parsing_directions closes the fd internally */
	if (parse_fc_color("map.cub") == 0)
		exit (1);
	map_parsing("map.cub");
	/* cleanup get_next_line internal buffers */
	gnl_cleanup();

	return (0);
}
