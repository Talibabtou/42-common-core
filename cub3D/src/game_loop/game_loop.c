/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:46:34 by bboissen          #+#    #+#             */
/*   Updated: 2024/09/17 15:51:02 by gdumas           ###   ########.fr       */
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
	t_player		*player;
	t_dda			wall_ray;
	double			ray_angle;
	int				x;

	x = 0;
	player = &(data->player);
	draw_floor_ceil(data, &data->framebuffer);
	while (x < SCREEN_WIDTH)
	{
		ray_angle = (x - SCREEN_WIDTH * 0.5) * data->ray.angle_step;
		init_ray(player->dir_angle + ray_angle, player, &data->ray);
		get_ray_config_dda(&data->ray);
		get_wall_config_dda(&(data->grid), &data->ray, &wall_ray, ray_angle);
		add_pixels_col_to_img_txt(data, x, &wall_ray, &data->ray);
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
	t_ray	ray;

	ray.angle_step = tan(to_rad(FOV) * 0.5) / SCREEN_WIDTH;
	data->ray = ray;
	mlx_hook(data->mlx.win_ptr, 17, 0L, exit_button, data);
	mlx_hook(data->mlx.win_ptr, 02, 1L << 0, key_press_hook, data);
	mlx_hook(data->mlx.win_ptr, 03, 1L << 1, key_release_hook, data);
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, (void *)data);
	mlx_loop(data->mlx.mlx_ptr);
}
