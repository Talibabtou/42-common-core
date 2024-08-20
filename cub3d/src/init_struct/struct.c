/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:01:09 by gemartel          #+#    #+#             */
/*   Updated: 2024/08/20 17:15:53 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub3d	*init_struct(void)
{
	t_cub3d	*data;

	data = calloc_gc(1, sizeof(t_cub3d), STRUCT);
	if (!data)
		print_and_exit_error(MALLOC_ERR_MSG);
	return (data);
}
