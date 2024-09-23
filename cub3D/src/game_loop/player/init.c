/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:47:16 by bboissen          #+#    #+#             */
/*   Updated: 2024/09/18 16:24:22 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Calculates the relative angle of the
 * player's direction based on the orientation.
 * 
 * @param orientation The orientation of the player.
 * @return The relative angle of the player's direction.
 */
static double	get_player_dir_relative_angle(char orientation)
{
	if (orientation == 'E')
		return (to_rad(0));
	else if (orientation == 'S')
		return (to_rad(90));
	else if (orientation == 'W')
		return (to_rad(180));
	else
		return (to_rad(270));
}

/**
 * @brief Gets the position of the player on the grid.
 * 
 * @param grid Pointer to the grid structure.
 * @return The position of the player.
 */
static t_dvector	get_player_pos(const t_grid *grid)
{
	int			i;
	int			j;
	t_dvector	pos;
	bool		flag;

	i = 0;
	flag = false;
	while (!flag && grid->content[i])
	{
		j = 0;
		while (!flag && grid->content[i][j])
		{
			if (is_player(grid->content[i][j]))
			{
				pos = (t_dvector){.x = j, .y = i};
				flag = true;
			}
			j++;
		}
		i++;
	}
	return (pos);
}

/**
 * @brief Adjusts the position of the player to the nearest walls.
 * 
 * @param grid_c The grid content.
 * @param player Pointer to the player structure.
 */
static void	adjust_player_pos_to_near_walls(char **grid_c, t_player *player)
{
	if (grid_c[(int)player->pos.y - 1][(int)player->pos.x])
		player->pos.y += 0.5;
	else if (grid_c[(int)player->pos.y + 1][(int)player->pos.x])
		player->pos.y -= 0.5;
	if (grid_c[(int)player->pos.y][(int)player->pos.x - 1])
		player->pos.x += 0.5;
	else if (grid_c[(int)player->pos.y][(int)player->pos.x + 1])
		player->pos.x -= 0.5;
}

/**
 * @brief Initializes the player.
 * 
 * @param grid Pointer to the grid structure.
 * @param player Pointer to the player structure.
 */
void	init_player(t_grid *grid, t_player *player)
{
	player->aspect_ratio = ((double)SCREEN_WIDTH / (double)SCREEN_HEIGHT);
	player->pos = get_player_pos(grid);
	player->dir_angle = get_player_dir_relative_angle
		(grid->content[(int)player->pos.y][(int)player->pos.x]);
	adjust_player_pos_to_near_walls(grid->content, player);
	process_player_dir(player);
	player_next_movement(player);
}
