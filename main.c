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

#include "main_helper.h"

int	check_file_name(char *filename)
{
	char	**str;
	int		valid;

	str = ft_split(filename, '.');
	if (!str || !str[0] || !str[1])
		return (free_split(str), 0);
	valid = (!ft_strncmp(str[1], "cub", ft_strlen(str[1]))
			&& ft_strlen(str[1]) == 3);
	free_split(str);
	return (valid);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		if (check_file_name(av[1]))
			run_game(av[1]);
		else
			printf("invalid map name\n");
	}
	return (0);
}
