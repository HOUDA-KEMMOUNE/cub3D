/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:57:34 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/22 10:57:35 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_helper.h"

void	check_map_position(char *file_name)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file_name, O_RDONLY);
	check_open(fd);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (i == 0 && ft_strnstr(line, "111", ft_strlen(line)) != NULL)
		{
			printf("Error\n");
			printf("Map should be at the end of the file !\n");
			close(fd);
			exit(1);
		}
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
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

void	check_open(int fd)
{
	if (fd < 0)
	{
		printf("Error\n");
		printf("Not a valid file :/\n");
		exit (1);
	}
}

void	fill_textures(char *line, char *text, t_texture *texture)
{
	char	**first_split;
	char	**second_split;

	first_split = ft_split(line, ' ');
	if (!first_split || !first_split[1])
	{
		free_split(first_split);
		return ;
	}
	second_split = ft_split(first_split[1], '\n');
	if (!second_split || !second_split[0])
	{
		free_split(first_split);
		free_split(second_split);
		return ;
	}
	assign_texture(text, second_split[0], texture);
	free_split(first_split);
	free_split(second_split);
}

void	check_if_map_exist(char *file_name)
{
	int		fd;
	int		flag;
	char	*line;

	fd = open(file_name, O_RDONLY);
	check_open(fd);
	flag = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strnstr(line, "1", ft_strlen(line)) != NULL)
			flag++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (flag < 3)
	{
		printf("Error\n");
		printf("Invalid map :/\n");
		exit(1);
	}
}
