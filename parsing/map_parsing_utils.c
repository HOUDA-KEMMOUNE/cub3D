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

void	maze_init(t_maze *maze)
{
	maze->first_line = NULL;
	maze->count = 0;
	maze->current_char = '1';
}
