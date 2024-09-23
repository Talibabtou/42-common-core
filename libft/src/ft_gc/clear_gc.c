/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_gc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:27:13 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/16 17:44:29 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	clear_gc(void)
{
	t_list	**gc_list;
	t_list	*tmp;

	gc_list = gc_ptr();
	tmp = *gc_list;
	while (tmp)
	{
		if (tmp->content)
		{
			free(tmp->content);
			tmp->content = NULL;
		}
		tmp = tmp->next;
	}
	ft_lstclear(gc_list, free);
	*gc_list = NULL;
}
