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

static int	check_path(char *path)
{
	int	fd;

	fd = open(path, O_RDWR);
	printf("path -> %s\n", path);
	if (fd < 0)
	{
		printf("fd => %d || Path doesn't exist :/\n", fd);
		return (0);
	}
	return (1);
}

static int	first_word(char *word, char *path, int *count)
{
	char	*new_path;

	if ((ft_strncmp(word, "NO", 2) == 0) || (ft_strncmp(word, "SO", 2) == 0)
		|| (ft_strncmp(word, "WE", 2) == 0) || (ft_strncmp(word, "EA", 2) == 0))
	{
		new_path = ft_strtrim(path, "./");
		printf("new path: %s\n", new_path);

		if (check_path(new_path) == 0)
		{
			exit (1);
		}
		(*count)++;
		free (new_path);
		return ((*count));
	}
	return (0);
}


int	parsing_map(int fd)
{
	int		count;
	char	*line;
	char	**s;
	int		i;

	i = 0;
	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		s = ft_split(line, ' ');
		if (first_word(s[0], s[1], &count) == 0)
		{
			// check_path(s[1]);
			if (count == 4)
			{
				exit (0);
			}
		}
	}
	if (count != 4)
	{
		printf("Invalid map :/\n");
		exit (1);
	}
	free(line);
	return (0);
}
