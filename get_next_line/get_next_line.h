/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:12:28 by hkemmoun          #+#    #+#             */
/*   Updated: 2024/12/18 16:51:55 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
// size_t	ft_strlen(char *s);
// char	*ft_strdup(char *str);
// char	*ft_strjoin(char *s1, char *s2);
// char	*ft_substr(char *s, unsigned int start, size_t len);
// char	*ft_strchr(char *s, int c);
char	*rest_char(char *line);
char	*get_line(char *buffer, char *rest, int fd);

#endif
