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

void	free_split(char **s)
{
    int i = 0;

    if (!s)
        return;
    while (s[i])
    {
        free(s[i]);   // free each string
        i++;
    }
    free(s);          // finally free the array itself
}
