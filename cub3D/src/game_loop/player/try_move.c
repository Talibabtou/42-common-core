/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:00:07 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/04 15:28:27 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Checks if a given position is within the bounds of the grid.
 * 
 * @param grid Pointer to the grid structure.
 * @param pos Pointer to the position vector.
 * @return True if the position is within bounds, false otherwise.
 */
static bool	is_within_bounds(t_grid *grid, t_ivector *pos)
{
	return (pos->x >= 0 && pos->x < grid->width
		&& pos->y >= 0 && pos->y < grid->height);
}

/**
 * @brief Checks if a given position is walkable based on the grid content.
 * 
 * @param grid Pointer to the grid structure.
 * @param pos1 Pointer to the first position vector.
 * @param pos2 Pointer to the second position vector.
 * @return True if the position is walkable, false otherwise.
 */
static bool	is_position_walkable(t_grid *grid, t_ivector *pos1, t_ivector *pos2)
{
	return (grid->content[pos1->y][pos1->x] != '1' &&
			grid->content[pos2->y][pos1->x] != '1' &&
			grid->content[pos1->y][pos2->x] != '1' &&
			grid->content[pos2->y][pos2->x] != '1');
}

/**
 * @brief Calculates the grid positions based on a given new position.
 * 
 * @param new Pointer to the new position vector.
 * @param grid_pos Pointer to the first grid position vector.
 * @param grid_pos2 Pointer to the second grid position vector.
 */
static void	get_grid_positions(t_dvector *new,
		t_ivector *grid_pos, t_ivector *grid_pos2)
{
	grid_pos->x = (int)(new->x + 0.3);
	grid_pos2->x = (int)(new->x - 0.3);
	grid_pos->y = (int)(new->y + 0.3);
	grid_pos2->y = (int)(new->y - 0.3);
}

/**
 * @brief Attempts to move the player to a new position based on the grid.
 * 
 * @param grid Pointer to the grid structure.
 * @param pos Pointer to the player's position vector.
 * @param dx The change in x-direction.
 * @param dy The change in y-direction.
 * @return True if the move is successful, false otherwise.
 */
bool	try_move(t_grid *grid, t_dvector *pos, double dx, double dy)
{
	t_dvector	new;
	t_ivector	grid_pos;
	t_ivector	grid_pos2;

	new.x = pos->x + dx;
	new.y = pos->y + dy;
	get_grid_positions(&new, &grid_pos, &grid_pos2);
	if (!is_within_bounds(grid, &grid_pos)
		|| !is_within_bounds(grid, &grid_pos2))
		return (false);
	if (is_position_walkable(grid, &grid_pos, &grid_pos2))
	{
		pos->x = new.x;
		pos->y = new.y;
		return (true);
	}
	return (false);
}
