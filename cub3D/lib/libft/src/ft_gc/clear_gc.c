/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_gc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:27:13 by hanglade          #+#    #+#             */
/*   Updated: 2024/09/12 19:27:22 by talibabtou       ###   ########.fr       */
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
