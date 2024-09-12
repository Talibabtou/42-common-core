/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:01:09 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/12 18:33:51 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Initializes and returns a pointer to a newly allocated t_cub3d structure.
 * 
 * @return A pointer to the newly allocated t_cub3d structure.
 */
t_cub3d	*init_struct(void)
{
	t_cub3d	*data;

	data = ft_gc(ft_calloc(1, sizeof(t_cub3d)));
	if (!data)
		print_and_exit_error(MALLOC_ERR_MSG);
	return (data);
}
