/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:38:29 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/10/16 16:38:31 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	rgb_size(char **rgb)
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
	return (1);
}

static int	check_range(int color_id)
{
	if (color_id >= 0 && color_id <= 255)
		return (1);
	printf("Invalid range\n");
	return (0);
}

static int	parse_rgb(char *s)
{
	char	**rgb;
	int		i;
	int		color_id;

	rgb = ft_split(s, ',');
	// printf("s --> %s\n", s);
	if (rgb_size(rgb) == 0)
	{
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
	return (1);
}

int	parse_fc_color(char *file)
{
	char	*line;
	char	**s;
	int		f;
	int		c;
	int		fd;

	f = 0;
	c = 0;
	fd = open(file, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		s = ft_split(line, ' ');
		if ((ft_strncmp(s[0], "F", 1) == 0) || (ft_strncmp(s[0], "C", 1) == 0))
		{
			if (ft_strncmp(s[0], "F", 1) == 0)
				f = 1;
			else
				c = 1;
			if (parse_rgb(s[1]) == 0)
				return (0);
		}
	}
	if (f == 1 && c == 1)
		return (1);
	printf("Invalid input for the floor/ceiling color :/\n");
	return (0);
}

static int	check_path(char *path)
{
	int	fd;

	if (path[0] == '\0')
	{
		printf("Write something in the path please :/\n");
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Path doesn't exist :/\n");
		return (0);
	}
	return (1);
}

// static int	first_word(char *word, char *path, int *count)
// {
// 	(void)count;
// 	int	so;
// 	int	we;
// 	int	ea;
// 	int	no;

// 	so = 0;
// 	we = 0;
// 	ea = 0;
// 	no = 0;
// 	if ((ft_strncmp(word, "NO", 2) == 0) || (ft_strncmp(word, "SO", 2) == 0)
// 		|| (ft_strncmp(word, "WE", 2) == 0) || (ft_strncmp(word, "EA", 2) == 0))
// 	{
// 		// printf("test\n");
// 		if (ft_strncmp(word, "NO", 2) == 0)
// 		{
// 			printf("no\n");
// 			no = 1;
// 		}
// 		else if (ft_strncmp(word, "SO", 2) == 0)
// 		{
// 			printf("so\n");
// 			so = 1;
// 		}
// 		else if (ft_strncmp(word, "EA", 2) == 0)
// 		{
// 			printf("ea\n");
// 			ea = 1;
// 		}
// 		else if (ft_strncmp(word, "WE", 2) == 0)
// 		{
// 			printf("we\n");
// 			we = 1;
// 		}
// 		if (check_path(path) == 0)
// 			exit (1);
// 		// (*count)++;
// 		free (path);
// 		// return ((*count));
// 	}
// 	if (no == 1 && so == 1 && ea == 1 && we == 1)
// 	{
// 		printf("Good!\n");
// 		return (1);
// 	}
// 	printf("Invalid input\n");
// 	return (0);
// }

static char	*first_word(char *word, char *path, int *count)
{
	(void)count;
	if ((ft_strncmp(word, "NO", 2) == 0) || (ft_strncmp(word, "SO", 2) == 0)
		|| (ft_strncmp(word, "WE", 2) == 0) || (ft_strncmp(word, "EA", 2) == 0))
	{
		if (check_path(path) == 0)
			exit (1);
		free (path);
		return (word);
	}
	return ("bad");
}


int	parsing_directions(int fd)
{
	int		count;
	char	*line;
	char	**s;
	int		i;
	char	*new_path;
	char	*res;
	int		direc[4];

	i = 0;
	count = 0;
	while (i < 4)
	{
		direc[i] = 0;
		i++;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		s = ft_split(line, ' ');
		new_path = ft_strtrim(s[1], "\n");
		res = first_word(s[0], new_path, &count);
		if (ft_strncmp(res, "SO", 2) == 0)
			direc[0] = 1;
		else if (ft_strncmp(res, "WE", 2) == 0)
			direc[1] = 1;
		else if (ft_strncmp(res, "EA", 2) == 0)
			direc[2] = 1;
		else if (ft_strncmp(res, "NO", 2) == 0)
			direc[3] = 1;
	}
	i = 0;
	while (i < 4)
	{
		if (direc[i] == 0)
		{
			printf("issue\n");
			exit (1);
		}
		i++;
	}
	free(line);
	free(new_path);
	return (0);
}
