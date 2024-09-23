/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:46:59 by bboissen          #+#    #+#             */
/*   Updated: 2024/09/17 11:19:03 by bboissen         ###   ########.fr       */
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
void	player_next_movement(t_player *player)
{
	player->movement.x = player->dir.x * PLAYER_STEP_SIZE;
	player->movement.y = player->dir.y * PLAYER_STEP_SIZE;
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
