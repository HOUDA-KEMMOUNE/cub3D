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

static int	first_word(char *word, int *count)
{	
	if ((ft_strncmp(word, "NO", 2) == 0) || (ft_strncmp(word, "SO", 2) == 0)
		|| (ft_strncmp(word, "WE", 2) == 0) || (ft_strncmp(word, "EA", 2) == 0))
	{
		// printf("The word is: %s\n", word);
		(*count)++;
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
		if (first_word(s[0], &count) == 0)
		{
			if (count == 4)
				exit (0);
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
