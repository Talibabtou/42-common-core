/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:30:48 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/03 22:29:32 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Checks if a texture path has already been set for a given direction.
 * 
 * @param index The direction to check.
 * @param text The structure containing the texture paths and their status.
 */
void	check_double_text(int index, t_text_file *text)
{
	if ((index == NORTH && text->no == true)
		|| (index == SOUTH && text->so == true)
		|| (index == WEST && text->we == true)
		|| (index == EAST && text->ea == true))
		free_and_exit_error(CONFIG_ERROR);
}

/**
 * @brief Saves a texture path for a given direction.
 * 
 * @param text_path The structure to store the texture path.
 * @param index The direction for which to save the texture path.
 * @param path The path to the texture file.
 */
void	save_text_path(t_text_file *text_path, int index, char *path)
{
	if (index == NORTH)
	{
		text_path->text[NORTH] = path;
		text_path->no = true;
	}
	else if (index == SOUTH)
	{
		text_path->text[SOUTH] = path;
		text_path->so = true;
	}
	else if (index == EAST)
	{
		text_path->text[EAST] = path;
		text_path->ea = true;
	}
	else if (index == WEST)
	{
		text_path->text[WEST] = path;
		text_path->we = true;
	}
}
