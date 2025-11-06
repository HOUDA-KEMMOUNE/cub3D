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

// void	check_empty_file(char *file)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open(file, O_RDONLY);
// 	line = get_next_line(fd);
// 	if (line == NULL)
// 	{
// 		close (fd);
// 		printf("Error\n");
// 		printf("Empty file :/\n");
// 		exit (1);
// 	}
// 	else
// 	{
// 		line = get_next_line(fd);
// 		printf("line --> %s\n", line);
// 		close (fd);
// 		return ;
// 	}
// }

int	main(void)
{
	int		fd;
	// char	*file_name;

	// file_name = "map.cub";
	// check_empty_file("map.cub");
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
