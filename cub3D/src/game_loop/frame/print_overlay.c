/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_overlay.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:14:49 by talibabtou        #+#    #+#             */
/*   Updated: 2024/09/04 15:26:13 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Retrieves the color of a specific pixel in the overlay image.
 * 
 * @param data Pointer to the main game structure.
 * @param overlay_x The x-coordinate of the pixel in the overlay image.
 * @param overlay_y The y-coordinate of the pixel in the overlay image.
 * @return The color of the specified pixel in the overlay image.
 */
static unsigned int	get_overlay_color(t_cub3d *data,
			int overlay_x, int overlay_y)
{
	char			*dst;
	unsigned int	color;

	dst = data->overlay.addr + (overlay_y * data->overlay.line_length
			+ overlay_x * (data->overlay.bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

/**
 * @brief Calculates the offsets needed to center
 * the overlay image on the screen.
 * 
 * @param data Pointer to the main game structure.
 * @param x_offset Pointer to store the calculated x-offset.
 * @param y_offset Pointer to store the calculated y-offset.
 */
static void	calculate_overlay_offsets(t_cub3d *data,
			int *x_offset, int *y_offset)
{
	*x_offset = (SCREEN_WIDTH - data->overlay.width) * 0.5;
	*y_offset = (SCREEN_HEIGHT - data->overlay.height) * 0.5;
}

/**
 * @brief Draws a column of the overlay image onto the framebuffer.
 * 
 * @param data Pointer to the main game structure.
 * @param x The x-coordinate of the column to draw.
 */
void	draw_overlay_column(t_cub3d *data, int x)
{
	int				y;
	unsigned int	color;
	int				overlay[2];
	int				offset[2];

	calculate_overlay_offsets(data, &offset[0], &offset[1]);
	overlay[0] = x - offset[0];
	if (overlay[0] >= 0 && overlay[0] < data->overlay.width)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			overlay[1] = y - offset[1];
			if (overlay[1] >= 0 && overlay[1] < data->overlay.height)
			{
				color = get_overlay_color(data, overlay[0], overlay[1]);
				if (color != 0 && color != 0xFF000000)
					put_pixel(&data->framebuffer, x, y, color);
			}
			y++;
		}
	}
}
