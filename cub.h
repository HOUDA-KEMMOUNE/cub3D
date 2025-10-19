/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:53:33 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/10/16 16:53:33 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>

// --------- Parsing ----------------
int		rgb_size(char **rgb);
int		check_range(int color_id);
int		parse_rgb(char *s);
int		parse_fc_color_helper(int *f, int *c, char *line);
int		parse_fc_color(char *file);
int		check_path(char *path);
char	*first_word(char *word, char *path);
char	*parsing_directions_helper(char *line, int *direc);
void	check_directions(int *direc);
int		parsing_directions(int fd);

#endif