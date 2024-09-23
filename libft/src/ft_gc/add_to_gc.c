/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_gc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:55:51 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/16 17:44:35 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	add_to_gc(void *ptr)
{
	t_list	*new_node;
	t_list	*tmp;

	if (!ptr)
		return ;
	tmp = *gc_ptr();
	while (tmp)
	{
		if (tmp->content == ptr)
			return ;
		tmp = tmp->next;
	}
	new_node = ft_lstnew(ptr);
	if (!new_node)
	{
		free(ptr);
		return ;
	}
	ft_lstadd_front(gc_ptr(), new_node);
}
