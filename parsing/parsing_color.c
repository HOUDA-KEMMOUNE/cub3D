/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 23:15:47 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/10/19 23:15:51 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	rgb_size(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		i++;
	}
	if (i != 3)
	{
		printf("You should enter 3 clors (red,green,blue)\n");
		return (0);
	}
	free_split(rgb);
	return (1);
}

int	check_range(int color_id)
{
	if (color_id >= 0 && color_id <= 255)
		return (1);
	printf("Invalid range\n");
	return (0);
}

int	parse_rgb(char *s)
{
	char	**rgb;
	int		i;
	int		color_id;

	rgb = ft_split(s, ',');
	if (rgb_size(rgb) == 0)
		return (0);
	i = 0;
	while (i < 3)
	{
		color_id = ft_atoi(rgb[i]);
		if (check_range(color_id) == 0)
			return (0);
		i++;
	}
	free_split(rgb);
	return (1);
}

int	parse_fc_color_helper(int *f, int *c, char *line)
{
	char	**s;

	s = ft_split(line, ' ');
	if ((ft_strncmp(s[0], "F", 1) == 0) || (ft_strncmp(s[0], "C", 1) == 0))
	{
		if (ft_strncmp(s[0], "F", 1) == 0)
			*f = 1;
		else
			*c = 1;
		if (parse_rgb(s[1]) == 0)
			return (0);
	}
	free_split(s);
	return (1);
}

int	parse_fc_color(char *file)
{
	char	*line;
	int		f;
	int		c;
	int		fd;

	f = 0;
	c = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (parse_fc_color_helper(&f, &c, line) == 0)
			return (0);
		line = get_next_line(fd);
	}
	if (f == 1 && c == 1)
		return (1);
	printf("Invalid input for the floor/ceiling color :/\n");
	free (line);
	close (fd);
	return (0);
}
