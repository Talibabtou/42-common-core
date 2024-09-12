/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:33:00 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/05 08:40:26 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Checks if a color has been previously set for the floor or ceiling.
 * 
 * @param colors Pointer to the t_colors structure containing color information.
 * @param index The index indicating whether
 * to check the floor (F) or ceiling (C).
 */
void	check_double_color(t_colors *colors, int index)
{
	if (index == F && colors->floor == true)
		free_and_exit_error(COLOR_DOUBLE_E);
	else if (index == C && colors->ceiling == true)
		free_and_exit_error(COLOR_DOUBLE_E);
}

/**
 * @brief Saves the RGB color values for the floor or ceiling.
 * 
 * @param colors Pointer to the t_colors structure containing color information.
 * @param rgb Array of three integers representing the RGB color values.
 * @param index_color The index indicating whether
 * to save the color for the floor (4) or ceiling (other).
 */
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
