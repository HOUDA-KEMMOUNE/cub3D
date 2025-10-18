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

# ifndef CUB_H
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
int     parsing_map(int fd);
int	    parse_fc_color(int fd);

# endif