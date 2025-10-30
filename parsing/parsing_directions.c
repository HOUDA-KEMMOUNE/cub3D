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
		printf("Error\n");
		printf("Write something in the path please :/\n");
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\n");
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
		{
			free (path);
			exit (1);
		}
		return (word);
	}
	return (NULL);
}

char	*parsing_directions_helper(char *line, int *direc)
{
	char	**s;
	char	*new_path;
	char	*res;

	s = ft_split(line, ' ');
	if (!s || !s[0] || !s[1])
    {
        free_split(s);
        return (NULL);
    }
	new_path = ft_strtrim(s[1], "\n");
	if (new_path == NULL)
    {
        free_split(s);
        return (NULL);
    }
	res = first_word(s[0], new_path);
	if (res == NULL)
    {
        free_split(s);
        free(new_path);
        return (NULL);
    }
	if (ft_strncmp(res, "SO", 2) == 0)
		direc[0] = 1;
	else if (ft_strncmp(res, "WE", 2) == 0)
		direc[1] = 1;
	else if (ft_strncmp(res, "EA", 2) == 0)
		direc[2] = 1;
	else if (ft_strncmp(res, "NO", 2) == 0)
		direc[3] = 1;
	free_split(s);
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
			printf("Error\n");
			printf("Check if you have: SO,WE,EA,NO in your file\n");
			exit (1);
		}
		i++;
	}
}

int	parsing_directions(int fd)
{
	//int		count;
	char	*line;
	int		i;
	char	*new_path;
	int		direc[4];

	i = 0;
	//count = 0;
	while (i < 4)
	{
		direc[i] = 0;
		i++;
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		new_path = parsing_directions_helper(line, &direc[0]);
		free(line);
		if (new_path)
            free(new_path);
		line = get_next_line(fd);
	}
	check_directions(&direc[0]);
	close (fd);
	return (0);
}
