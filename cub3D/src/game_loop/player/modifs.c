/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:47:10 by bboissen          #+#    #+#             */
/*   Updated: 2024/09/17 11:36:48 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Manages the player's movement based on WASD keys.
 * 
 * @param key Pointer to the key handling structure.
 * @param player Pointer to the player structure.
 * @param move_wanted Pointer to the intended movement vector.
 */
static void	key_manage_wasd(const t_key_handl *key,
			t_player *player, t_dvector *move_wanted)
{
	if (key->w == 1)
	{
		move_wanted->x += player->movement.x;
		move_wanted->y += player->movement.y;
	}
	if (key->s == 1)
	{
		move_wanted->x -= player->movement.x;
		move_wanted->y -= player->movement.y;
	}
	if (key->a == 1)
	{
		move_wanted->x += player->movement.y;
		move_wanted->y -= player->movement.x;
	}
	if (key->d == 1)
	{
		move_wanted->x -= player->movement.y;
		move_wanted->y += player->movement.x;
	}
}

/**
 * @brief Modifies the player's position based on the intended movement.
 * 
 * @param key Pointer to the key handling structure.
 * @param player Pointer to the player structure.
 * @param grid Pointer to the grid structure.
 */
static void	modif_player_pos(t_key_handl *key, t_player *player, t_grid *grid)
{
	t_dvector	move_wanted;
	t_dvector	new;
	double		magnitude;

	new.x = player->pos.x;
	new.y = player->pos.y;
	move_wanted = (t_dvector){0, 0};
	key_manage_wasd(key, player, &move_wanted);
	magnitude = sqrt(move_wanted.x * move_wanted.x
			+ move_wanted.y * move_wanted.y);
	if (magnitude > 0)
	{
		move_wanted.x = (move_wanted.x / magnitude) * PLAYER_STEP_SIZE;
		move_wanted.y = (move_wanted.y / magnitude) * PLAYER_STEP_SIZE;
	}
	if (!try_move(grid, &new, move_wanted.x, move_wanted.y))
	{
		if (!try_move(grid, &new, move_wanted.x, 0))
			try_move(grid, &new, 0, move_wanted.y);
	}
	player->pos.x = new.x;
	player->pos.y = new.y;
}

/**
 * @brief Modifies the player's direction based on left and right arrow keys.
 * 
 * @param key Pointer to the key handling structure.
 * @param player Pointer to the player structure.
 */
static void	modif_player_dir(t_key_handl *key, t_player *player)
{
	if (key->left == 1)
	{
		player->dir_angle -= PLAYER_ROT_SPEED;
		if (player->dir_angle < 0)
			player->dir_angle += 2 * PI;
	}
	if (key->right == 1)
	{
		player->dir_angle += PLAYER_ROT_SPEED;
		if (player->dir_angle > 2 * PI)
			player->dir_angle -= 2 * PI;
	}
	process_player_dir(player);
	player_next_movement(player);
}

/**
 * @brief Modifies the player's position and direction based on key inputs.
 * 
 * @param data Pointer to the main game structure.
 * @return 0 on success.
 */
int	modif_player(t_cub3d *data)
{
	modif_player_pos(&(data->key), &(data->player), &(data->grid));
	modif_player_dir(&(data->key), &(data->player));
	return (false);
}
