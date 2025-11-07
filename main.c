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

void	check_map_position(char *file_name)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\n");
		printf("File doesn't exist :/\n");
		exit (1);
	}
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (i == 0 && ft_strnstr(line, "111", ft_strlen(line)) != NULL)
		{
			printf("Error\n");
			printf("Map should be at the end of the file !\n");
			close (fd);
			exit (1);
		}
		i++;
		free (line);
		line = get_next_line(fd);
	}
}

// void	empty_line(char *line)
// {
// 	int	i;
// 	int	flag;

// 	i = 0;
// 	flag = 0;
// 	if (line == NULL)
// 	{
// 		printf("empty line (empty_line finction)\n");
// 		return ;
// 	}

// 	while (line[i])
// 	{
// 		if (line[i] == ' ' || line[i] == '\t')
// 			i++;
// 		else
// 		{
// 			flag = 1;
// 			i++;
// 		}
// 	}
// 	if (flag == 0)
// 	{

// 	}
// }

void	check_if_map_exist(char *file_name)
{
	int		fd;
	char	*line;
	int		i;
	int		flag;
	int		count;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\n");
		printf("File doesn't exist :/\n");
		exit (1);
	}
	line = get_next_line(fd);
	count = 0;
	while (line != NULL)
	{
		i = 0;
		// flag = 0;
		// printf("line --> %s\n", line);
		if (ft_strnstr(line, "NO", ft_strlen(line)) != NULL)
			count++;
		else if (ft_strnstr(line, "SO", ft_strlen(line)) != NULL)
			count++;
		else if (ft_strnstr(line, "WE", ft_strlen(line)) != NULL)
			count++;
		else if (ft_strnstr(line, "EA", ft_strlen(line)) != NULL)
			count++;
		else if (ft_strnstr(line, "C", ft_strlen(line)) != NULL)
			count++;
		else if (ft_strnstr(line, "F", ft_strlen(line)) != NULL)
			count++;
		if (count == 6)
		{
			// free (line);
			break ;
		}
		free (line);
		line = get_next_line(fd);
	}
	// printf("line (after loop) --> %s\n", line);
	flag = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		// printf("line (second loop) --> {%s}\n", line);
		i = 0;
		// printf("line[%d] (second loop) --> {%c}\n", i, line[i]);
		while (line[i] != '\n')
		{
			if (line[i] == '\0' || line[i] == '\n' || (i == 0 && (line[i] == ' ' || line[i] == '\t')))
			{
				line = get_next_line(fd);
				// free (line);
				break;
			}
			if (i == 0 && line[i] == '1')
			{
				if (line[i + 1] != '\0' && (line[i] == '1' || line[i] == '0' || line[i] == ' ' 
					|| line[i] == '\t' || line[i] == 'N' || line[i] == 'S' 
					|| line[i] == 'E' || line[i] == 'W'))
				{
					flag++;
					break ;
				}
				i++;
			}
		}
		free (line);
		line = get_next_line(fd);
	}
	if (flag < 3)
	{
		printf("Error\n");
		printf("Invalid map :/\n");
		exit (1);
	}
	close (fd);
}

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
	check_if_map_exist("map.cub");
	check_map_position("map.cub");
	map_parsing("map.cub");
	/* cleanup get_next_line internal buffers */
	gnl_cleanup();

	return (0);
}
