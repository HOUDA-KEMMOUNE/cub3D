/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:21:33 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/22 10:21:35 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	rgb_size(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (ft_strncmp(rgb[i], "\n", 1) == 0)
		{
			printf("Error\n");
			printf("You should enter 3 clors (red,green,blue)\n");
			exit (1);
		}
		i++;
	}
	if (i != 3)
	{
		printf("Error\n");
		printf("You should enter 3 clors (red,green,blue)\n");
		return (0);
	}
	return (1);
}

int	check_range(int color_id)
{
	if (color_id >= 0 && color_id <= 255)
		return (1);
	printf("Error\n");
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
	{
		free_split(rgb);
		return (0);
	}
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

int	rgb_to_int(char *rgb_str)
{
	char	**split;
	int		r;
	int		g;
	int		b;
	int		color;

	split = ft_split(rgb_str, ',');
	if (! split || rgb_size(split) == 0)
	{
		free_split(split);
		return (0);
	}
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_split(split);
	color = (r << 16) | (g << 8) | b;
	return (color);
}
