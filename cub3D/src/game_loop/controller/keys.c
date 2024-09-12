/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:56:51 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/12 19:04:19 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Handles key press events for the game
 * 
 * @param key The key code of the pressed key
 * @param data Pointer to the main game structure
 * @return 0 on success
 */
int	key_press_hook(int key, t_cub3d *data)
{
	if (key == XK_w)
		data->key.w = 1;
	else if (key == XK_s)
		data->key.s = 1;
	else if (key == XK_a)
		data->key.a = 1;
	else if (key == XK_d)
		data->key.d = 1;
	else if (key == XK_Left)
		data->key.left = 1;
	else if (key == XK_Right)
		data->key.right = 1;
	else if (key == XK_Escape)
		close_program(data, "Game exited via ESC.", EXIT_SUCCESS);
	return (false);
}

/**
 * @brief Handles key release events for the game
 * 
 * @param key The key code of the released key
 * @param data Pointer to the main game structure
 * @return 0 on success
 */
int	key_release_hook(int key, t_cub3d *data)
{
	if (key == XK_w)
		data->key.w = 0;
	else if (key == XK_s)
		data->key.s = 0;
	else if (key == XK_a)
		data->key.a = 0;
	else if (key == XK_d)
		data->key.d = 0;
	else if (key == XK_Left)
		data->key.left = 0;
	else if (key == XK_Right)
		data->key.right = 0;
	return (false);
}

/**
 * @brief Handles the window close event for the game
 * 
 * @param cub3d Pointer to the main game structure
 * @return 0 on success
 */
int	exit_button(t_cub3d *cub3d)
{
	close_program(cub3d, "Game exited via window.", EXIT_SUCCESS);
	return (false);
}
