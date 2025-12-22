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

static void	set_fc_flag(int *f, int *c, char *id)
{
	if (ft_strncmp(id, "F", 1) == 0)
		*f = 1;
	else if (ft_strncmp(id, "C", 1) == 0)
		*c = 1;
}

static int	check_line_color(char *line)
{
	char	*p;

	p = line;
	if (*p == 'F' || *p == 'C')
		p++;
	while (*p && (*p == ' ' || *p == '\t'))
		p++;
	if (parse_rgb(p) == 0)
		return (0);
	return (1);
}

int	parse_fc_color_helper(int *f, int *c, char *line)
{
	char	**s;

	s = ft_split(line, ' ');
	if (!s || !s[0])
	{
		free_split(s);
		return (1);
	}
	if (ft_strncmp(s[0], "F", 1) == 0
		|| ft_strncmp(s[0], "C", 1) == 0)
	{
		set_fc_flag(f, c, s[0]);
		if (check_line_color(line) == 0)
		{
			free_split(s);
			return (0);
		}
	}
	free_split(s);
	return (1);
}

static int	parse_fc_loop(int fd, int *f, int *c)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (parse_fc_color_helper(f, c, line) == 0)
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	parse_fc_color(char *file)
{
	int		f;
	int		c;
	int		fd;

	f = 0;
	c = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	if (parse_fc_loop(fd, &f, &c) == 0)
		return (0);
	if (f == 1 && c == 1)
		return (1);
	printf("Error\n");
	printf("Invalid input for the floor/ceiling color :/\n");
	return (0);
}
