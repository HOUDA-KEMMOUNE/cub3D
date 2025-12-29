/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:56:11 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/10/20 15:56:14 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parsing.h"
#include "main_helper.h"

void	assign_texture(char *id, char *value, t_texture *texture)
{
	if (ft_strncmp(id, "NO", 2) == 0)
		texture->no = ft_strdup(value);
	else if (ft_strncmp(id, "SO", 2) == 0)
		texture->so = ft_strdup(value);
	else if (ft_strncmp(id, "WE", 2) == 0)
		texture->we = ft_strdup(value);
	else if (ft_strncmp(id, "EA", 2) == 0)
		texture->ea = ft_strdup(value);
	else if (ft_strncmp(id, "C", 1) == 0)
		texture->c = ft_strdup(value);
	else if (ft_strncmp(id, "F", 1) == 0)
		texture->f = ft_strdup(value);
}

void	free_split(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}
