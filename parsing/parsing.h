/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 23:47:24 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/10/19 23:47:29 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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

// --------- struct for the maze ----------

typedef struct s_maze
{
	char	*first_line;
	int		column;
	int		max_row;
	char	current_char;
	char	**map;
}	t_maze;

// --------- spawn player flags ----------

typedef struct s_flags
{
	int	n;
	int	s;
	int	e;
	int	w;
}	t_flags;

// --------- textures ----------

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*c;
	char	*f;
	int		c_int;
	int		f_int;
}	t_texture;

// --------- player ----------

typedef enum e_player_type
{
	north,
	south,
	east,
	west
}	t_player_type;

typedef struct s_player
{
	char			p;
	double			pos_x;
	double			pos_y;
	double			angle;
	t_player_type	type;
}	t_player;

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
void	parse_space(t_maze *maze, char **map, int x, int y);
void	maze_max_row(t_maze *maze, int fd, char *line);
void	map_array(t_maze *maze, int row, int column, int fd);
// void	check_empty_line(char **map);
void	map_parsing(char *file_name, t_maze *maze, t_player *player);
void	maze_init(t_maze *maze);
void	print_maze_struct(t_maze *maze);
void	flags_init(t_flags *flags);
int		skip_spaces_helper(char *s, int *px);
int		rgb_to_int(char *rgb_str);
void	parse_space_error_msg(void);
void	check_first_nd_last_line(char **map, int last_column);
void	check_stars(char **map, int last_column);
void	check_map_mid(char **map);
int		count_map_lines(int fd);
void	invalid_character(char **map);
void	check_zero(int y, int x, char **map);
void	filling_struct_map(t_maze *maze, int row, int column);
void	map_filling(t_maze *maze, int fd, char *file_name);
void	spawn_check(t_maze *maze, char **map);
void	parse_midle_space(t_maze *maze, char **map);
void	player_init(char **map, t_player *player);
void	player_position(t_player *player, char p, int y, int x);
void	check_player(char **map, int x, int y);
int		is_border_space(t_maze *maze, char **map, int x, int y);
// ----------- utils -----------
void	free_split(char **s);
#endif
// end of parsing.h
