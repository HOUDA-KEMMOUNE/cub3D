/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:35:06 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/10/21 16:35:08 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_maze_struct(t_maze *maze)
{
	printf("maze->first_line ==> %s\n", maze->first_line);
	printf("maze->column ==> %d\n", maze->column);
	printf("maze->current_char ==> %c\n", maze->current_char);
}

void	maze_init(t_maze *maze)
{
	maze->first_line = NULL;
	maze->column = 0;
	maze->max_row = 0;
	maze->current_char = '1';
	maze->map = NULL;
}

void	flags_init(t_flags *flags)
{
	flags->e = 0;
	flags->s = 0;
	flags->n = 0;
	flags->w = 0;
}

int	skip_spaces_helper(char *s, int *px)
{
	int	i;

	i = *px;
	if ((s[i] == ' ' || s[i] == '\t') && i == 0)
	{
		while (s[i] == ' ' || s[i] == '\t')
		{
			if (s[i] == '\0')
			{
				return (0);
				// break ;
			}
			i++;
		}
	}
	*px = i;
	return (1);
}
