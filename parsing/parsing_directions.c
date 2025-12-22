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

static char	*prepare_new_path(char **s)
{
	char	*new_path;

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
	if (first_word(s[0], new_path) == NULL)
	{
		free_split(s);
		free(new_path);
		return (NULL);
	}
	return (new_path);
}

char	*parsing_directions_helper(char *line, int *direc)
{
	char	**s;
	char	*new_path;

	s = ft_split(line, ' ');
	new_path = prepare_new_path(s);
	if (new_path == NULL)
		return (NULL);
	if (ft_strncmp(s[0], "SO", 2) == 0)
		direc[0] = 1;
	else if (ft_strncmp(s[0], "WE", 2) == 0)
		direc[1] = 1;
	else if (ft_strncmp(s[0], "EA", 2) == 0)
		direc[2] = 1;
	else if (ft_strncmp(s[0], "NO", 2) == 0)
		direc[3] = 1;
	free_split(s);
	return (new_path);
}

static void	process_lines(int fd, int *direc, char *line)
{
	char	*new_path;

	while (line != NULL)
	{
		new_path = parsing_directions_helper(line, direc);
		free(line);
		if (new_path)
			free(new_path);
		line = get_next_line(fd);
	}
}

int	parsing_directions(int fd)
{
	char	*line;
	int		i;
	int		direc[4];

	i = 0;
	while (i < 4)
	{
		direc[i] = 0;
		i++;
	}
	line = get_next_line(fd);
	if (line == NULL)
	{
		close(fd);
		printf("Error\n");
		printf("Empty file :/\n");
		exit(1);
	}
	process_lines(fd, &direc[0], line);
	check_directions(&direc[0]);
	close(fd);
	return (0);
}
