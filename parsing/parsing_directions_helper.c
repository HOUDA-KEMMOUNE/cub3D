/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_directions_helper.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:38:06 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/22 10:38:08 by hkemmoun         ###   ########.fr       */
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
