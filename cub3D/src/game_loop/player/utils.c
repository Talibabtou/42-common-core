/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:57:18 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/04 15:28:47 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Checks if a given character represents a player orientation.
 * 
 * @param c The character to check.
 * @return True if the character represents a player orientation,
 * false otherwise.
 */
bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

/**
 * @brief Converts degrees to radians.
 * 
 * @param degrees The angle in degrees.
 * @return The equivalent angle in radians.
 */
double	to_rad(int degrees)
{
	return (degrees * PI / 180);
}

/**
 * @brief Updates the player's movement vector based on their direction.
 * 
 * @param player Pointer to the player structure.
 */
void	process_player_movement(t_player *player)
{
	player->movement.x = cos(player->dir_angle) * PLAYER_STEP_SIZE;
	player->movement.y = sin(player->dir_angle) * PLAYER_STEP_SIZE;
}

/**
 * @brief Updates the player's direction vector based on their direction angle.
 * 
 * @param player Pointer to the player structure.
 */
void	process_player_dir(t_player *player)
{
	player->dir.x = cos(player->dir_angle);
	player->dir.y = sin(player->dir_angle);
}

/**
 * @brief Updates the player's plane vector based on their direction.
 * 
 * @param player Pointer to the player structure.
 */
void	process_player_plane(t_player *player)
{
	player->plane.x = -player->dir.y * player->plane_fov;
	player->plane.y = player->dir.x * player->plane_fov * player->aspect_ratio;
}
