/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:57:34 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/05 08:17:29 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Creates the raycast image.
 * 
 * @param data Pointer to the main data structure.
 */
static void	create_raycast_img(t_cub3d *data)
{
	t_ray		ray;
	t_player	*player;
	t_dda		wall_ray;
	double		camera_x;
	int			x;

	x = 0;
	player = &(data->player);
	draw_floor_ceil(data, &data->framebuffer);
	while (x < SCREEN_WIDTH)
	{
		camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		init_ray(camera_x, player, &ray);
		get_ray_config_dda(&ray);
		get_wall_config_dda(&(data->grid), &ray, &wall_ray);
		add_pixels_col_to_img_txt(data, x, &wall_ray, &ray);
		x++;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr,
		data->mlx.win_ptr, data->framebuffer.img_ptr, 0, 0);
}

/**
 * @brief The main game loop.
 * 
 * @param data Pointer to the main data structure.
 * @return 0 if the game loop is successful.
 */
int	game_loop(t_cub3d *data)
{
	modif_player(data);
	create_raycast_img(data);
	return (false);
}

/**
 * @brief The game event loop.
 * 
 * @param data Pointer to the main data structure.
 */
void	game_event_loop(t_cub3d *data)
{
	mlx_hook(data->mlx.win_ptr, 17, 0L, exit_button, data);
	mlx_hook(data->mlx.win_ptr, 02, 1L << 0, key_press_hook, data);
	mlx_hook(data->mlx.win_ptr, 03, 1L << 1, key_release_hook, data);
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, (void *)data);
	mlx_loop(data->mlx.mlx_ptr);
}
