/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:45:00 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/12/22 11:45:02 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HELPER_H
# define MAIN_HELPER_H

# include "parsing/parsing.h"
# include "raycasting/raycasting.h"

void	check_open(int fd);
void	fill_textures(char *line, char *text, t_texture *texture);
void	textures_init(char *file_name, t_texture *texture);
void	check_if_map_exist(char *file_name);
void	check_map_position(char *file_name);
void	run_game(void);

#endif
