/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_one_gc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:25:41 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/17 15:38:38 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	del_first_gc(t_list **alst, t_list *tmp)
{
	*alst = tmp->next;
	if (tmp->content)
	{
		free(tmp->content);
		tmp->content = NULL;
	}
	ft_lstdelone(tmp, free);
	tmp = NULL;
}

void	del_one_gc(void *ptr_to_free)
{
	t_list	**alst;
	t_list	*tmp;
	t_list	*prev_el;

	alst = gc_ptr();
	tmp = *alst;
	if (tmp && tmp->content == ptr_to_free)
		return (del_first_gc(alst, tmp));
	while (tmp && tmp->content != ptr_to_free)
	{
		prev_el = tmp;
		tmp = tmp->next;
	}
	if (tmp && tmp->content == ptr_to_free)
	{
		prev_el->next = tmp->next;
		if (tmp->content)
		{
			free(tmp->content);
			tmp->content = NULL;
		}
		ft_lstdelone(tmp, free);
		tmp = NULL;
	}
}
