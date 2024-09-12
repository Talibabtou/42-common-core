/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:57:45 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/12 20:23:01 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Creates a new sprite texture from a file path.
 * 
 * @param data The game data structure containing
 * the mlx and texture path information.
 * @param i The index of the texture path in the data structure.
 * @return A t_texture structure containing
 * the sprite's image reference and pixel data.
 */
t_texture	new_sprite(t_cub3d *data, int i)
{
	t_texture	sprite;

	sprite.reference = mlx_xpm_file_to_image(data->mlx.mlx_ptr,
			data->text_path.text[i], &sprite.x, &sprite.y);
	if (!sprite.reference)
		free_and_exit_error(MLX_SPRITE_ERROR);
	sprite.pixels = (unsigned char *)mlx_get_data_addr(sprite.reference,
			&sprite.bits_per_pixel, &sprite.line_len, &sprite.endian);
	return (sprite);
}

/**
 * Initializes all sprite textures.
 * 
 * @param data The game data structure containing
 * the mlx and texture path information.
 */
void	init_sprites(t_cub3d *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->text_img[i] = new_sprite(data, i);
		i++;
	}
}

/**
 * Initializes the overlay image for the game.
 * 
 * @param data The game data structure containing
 * the mlx and overlay information.
 */
void	init_overlay(t_cub3d *data)
{
	int	width;
	int	height;

	data->overlay.img = mlx_xpm_file_to_image(data->mlx.mlx_ptr,
			"sprites/iphone14promax.xpm", &width, &height);
	if (!data->overlay.img)
		free_and_exit_error(OVERLAY_ERROR);
	data->overlay.addr = mlx_get_data_addr(data->overlay.img,
			&data->overlay.bits_per_pixel, &data->overlay.line_length,
			&data->overlay.endian);
	data->overlay.width = width;
	data->overlay.height = height;
}
