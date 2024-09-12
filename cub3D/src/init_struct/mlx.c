/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:57:41 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/12 18:37:58 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Initializes the image for the game.
 * 
 * @param data The game data structure containing the
 * mlx and framebuffer information.
 */
void	init_image(t_cub3d *data)
{
	data->framebuffer.img_ptr = mlx_new_image(data->mlx.mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->framebuffer.img_ptr)
		free_and_exit_error(MLX_IMG_ERROR);
	data->framebuffer.addr = mlx_get_data_addr(data->framebuffer.img_ptr,
			&data->framebuffer.bpp, &data->framebuffer.line_len,
			&data->framebuffer.endian);
}

/**
 * Initializes the mlx structure for the game.
 * 
 * @param mlx The mlx structure to be initialized.
 */
void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->win_ptr = NULL;
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		free_and_exit_error(MLX_PTR_ERROR);
	add_to_gc(mlx->mlx_ptr);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
}
