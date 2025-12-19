/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:14:11 by hkemmoun          #+#    #+#             */
/*   Updated: 2024/11/19 00:05:15 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_fun(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr_s1;
	char	*ptr;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	ptr_s1 = (char *)s1;
	start = 0;
	end = ft_strlen(ptr_s1);
	while (ptr_s1[start] && set_fun(ptr_s1[start], set) == 1)
		start++;
	while (end > start && set_fun(ptr_s1[end - 1], set) == 1)
		end--;
	ptr = (char *)malloc((end - start + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	ft_strlcpy(ptr, &ptr_s1[start + i], end - start + 1);
	return (ptr);
}
