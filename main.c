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
#include "raycasting/raycasting.h"

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
	flag = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
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

void	fill_textures(char *line, char *text, t_texture *texture)
{
	char	**first_split;
	char	**second_split;

	first_split = ft_split(line, ' ');
	second_split = ft_split(first_split[1], '\n');
	if (ft_strncmp(text, "NO", 2) == 0)
		texture->no = second_split[0];
	else if (ft_strncmp(text, "SO", 2) == 0)
		texture->so = second_split[0];
	else if (ft_strncmp(text, "WE", 2) == 0)
		texture->we = second_split[0];
	else if (ft_strncmp(text, "EA", 2) == 0)
		texture->ea = second_split[0];
	else if (ft_strncmp(text, "C", 1) == 0)
		texture->c = second_split[0];
	else if (ft_strncmp(text, "F", 1) == 0)
		texture->f = second_split[0];
}

void	check_open(int fd)
{
	if (fd < 0)
	{
		printf("Error\n");
		printf("Not a valid file :/\n");
		exit (1);
	}
}

void	textures_init(char *file_name, t_texture *texture)
{
	int			fd;
	char		*line;

	fd = open(file_name, O_RDONLY);
	check_open(fd);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strnstr(line, "NO", ft_strlen(line)) != NULL)
			fill_textures(line, "NO", texture);
		else if (ft_strnstr(line, "SO", ft_strlen(line)) != NULL)
			fill_textures(line, "SO", texture);
		else if (ft_strnstr(line, "WE", ft_strlen(line)) != NULL)
			fill_textures(line, "WE", texture);
		else if (ft_strnstr(line, "EA", ft_strlen(line)) != NULL)
			fill_textures(line, "EA", texture);
		else if (ft_strnstr(line, "C", ft_strlen(line)) != NULL)
			fill_textures(line, "C", texture);
		else if (ft_strnstr(line, "F", ft_strlen(line)) != NULL)
			fill_textures(line, "F", texture);
		free (line);
		line = get_next_line(fd);
	}
}

int	main(void)
{
	int			fd;
	t_texture	*texture;
	t_maze		*maze;
	t_player	*player;
	t_game		game;

	fd = open("map.cub", O_RDONLY);
	texture = malloc(sizeof(t_texture));
	player = malloc(sizeof(t_player));
	maze = malloc(sizeof(t_maze));
	
	if (! texture || !player || !maze)
	{
		printf("Error\nMemory allocation failed\n");
		return (1);
	}
	
	if (fd < 0)
	{
		printf("Error\nNot a valid file :/\n");
		free(texture);
		free(player);
		free(maze);
		return (1);
	}
	
	if (parsing_directions(fd) == 1)
	{
		close(fd);
		free(texture);
		free(player);
		free(maze);
		exit (1);
	}
	
	if (parse_fc_color("map.cub") == 0)
	{
		free(texture);
		free(player);
		free(maze);
		exit (1);
	}
	
	textures_init("map.cub", texture);
	texture->c_int = rgb_to_int(texture->c);
	texture->f_int = rgb_to_int(texture->f);
	
	check_if_map_exist("map.cub");
	check_map_position("map.cub");
	map_parsing("map.cub", maze, player);
	gnl_cleanup();
	
	game.player = player;
	game.texture = texture;
	game.maze = maze;
	init_player_direction(player);
	start_cub3D(&game);
	return (0);
}
