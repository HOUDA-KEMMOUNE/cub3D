/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:38:51 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/10/16 16:38:54 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main()
{
	int	fd;

	fd = open("map.cub", O_RDONLY);
	if (fd < 0)
	{
		printf("Not a valid file :/\n");
		return (1);
	}
	printf("Good for u ;D\n");
	parsing_map(fd, "map.cub"); //TO_DO
}
