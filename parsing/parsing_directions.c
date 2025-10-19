/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_directions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 23:14:54 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/10/19 23:14:58 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_path(char *path)
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

char	*first_word(char *word, char *path)
{
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

char	*parsing_directions_helper(char *line, int *direc)
{
	char	**s;
	char	*new_path;
	char	*res;
	int		i;

	i = 0;
	s = ft_split(line, ' ');
	new_path = ft_strtrim(s[1], "\n");
	res = first_word(s[0], new_path);
	if (ft_strncmp(res, "SO", 2) == 0)
		direc[0] = 1;
	else if (ft_strncmp(res, "WE", 2) == 0)
		direc[1] = 1;
	else if (ft_strncmp(res, "EA", 2) == 0)
		direc[2] = 1;
	else if (ft_strncmp(res, "NO", 2) == 0)
		direc[3] = 1;
	return (new_path);
}

void	check_directions(int *direc)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (direc[i] == 0)
		{
			printf("Check if you have: SO,WE,EA,NO in your file\n");
			exit (1);
		}
		i++;
	}
}

int	parsing_directions(int fd)
{
	int		count;
	char	*line;
	int		i;
	char	*new_path;
	int		direc[4];

	i = 0;
	count = 0;
	while (i < 4)
	{
		direc[i] = 0;
		i++;
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		new_path = parsing_directions_helper(line, &direc[0]);
		line = get_next_line(fd);
	}
	check_directions(&direc[0]);
	free(line);
	free(new_path);
	return (0);
}
