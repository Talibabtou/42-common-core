/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:33:00 by gemartel          #+#    #+#             */
/*   Updated: 2024/08/20 17:15:58 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_double_color(t_colors *colors, int index)
{
	if (index == F && colors->floor == 1)
		free_and_exit_error(COLOR_DOUBLE_E);
	else if (index == C && colors->ceiling == 1)
		free_and_exit_error(COLOR_DOUBLE_E);
}

void	save_color(t_colors *colors, int *rgb, int index_color)
{
	if (index_color == 4)
	{
		colors->floor_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
		colors->floor = true;
	}
	else
	{
		colors->ceiling_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
		colors->ceiling = true;
	}
}
