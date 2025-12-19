/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:33:33 by hkemmoun          #+#    #+#             */
/*   Updated: 2024/11/16 07:49:33 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*current;

	current = *lst;
	while (current != NULL)
	{
		ptr = current->next;
		ft_lstdelone(current, del);
		current = ptr;
	}
	*lst = NULL;
}
