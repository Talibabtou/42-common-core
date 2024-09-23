/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:47:34 by bboissen          #+#    #+#             */
/*   Updated: 2024/09/17 15:51:51 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Puts a pixel on the image at a specified position with a given color.
 * 
 * @param img Pointer to the image structure.
 * @param col The column (x-coordinate) of the pixel.
 * @param line The line (y-coordinate) of the pixel.
 * @param color The color of the pixel.
 */
void	put_pixel(t_image *img, int col, int line, int color)
{
	int	offset;

	offset = (img->line_len * line) + (img->bpp * col / 8);
	if (col >= 0 && col < SCREEN_WIDTH && line >= 0 && line < SCREEN_HEIGHT)
		*((int *)(img->addr + offset)) = color;
}

/**
 * @brief Draws the floor and ceiling of the game environment.
 * 
 * @param data Pointer to the main game structure.
 * @param img Pointer to the image structure.
 */
void	draw_floor_ceil(t_cub3d *data, t_image *img)
{
	int	i;
	int	j;
	int	half_screen_height;

	half_screen_height = (int) SCREEN_HEIGHT * 0.5;
	i = 0;
	while (i < half_screen_height)
	{
		j = -1;
		while (++j < SCREEN_WIDTH)
			put_pixel(img, j, i, data->colors.ceiling_color);
		i++;
	}
	while (i < SCREEN_HEIGHT)
	{
		j = -1;
		while (++j < SCREEN_WIDTH)
			put_pixel(img, j, i, data->colors.floor_color);
		i++;
	}
}

/**
 * @brief Calculates the x-coordinate of a
 * texture based on the ray's position and direction.
 * 
 * @param ray Pointer to the ray structure.
 * @param wall Pointer to the wall structure.
 * @param texture Pointer to the texture structure.
 * @return The x-coordinate of the texture.
 */
static int	get_texture_x(t_ray *ray, t_dda *wall, t_texture *texture)
{
	double	wall_hit_pos;
	int		tex_x;

	if (wall->orientation == 'N' || wall->orientation == 'S')
		wall_hit_pos = ray->head_pos.x + wall->dist * ray->dir.x;
	else
		wall_hit_pos = ray->head_pos.y + wall->dist * ray->dir.y;
	wall_hit_pos -= floor(wall_hit_pos);
	tex_x = (int)(wall_hit_pos * (double)texture->x);
	return (tex_x);
}

/**
 * @brief Selects the appropriate texture based on the orientation of the wall.
 * 
 * @param data Pointer to the main game structure.
 * @param wall_orientation The orientation of the wall.
 * @return Pointer to the texture structure.
 */
static t_texture	*texture_to_display(t_cub3d *data, char wall_orientation)
{
	if (wall_orientation == 'N')
		return (&data->text_img[NORTH]);
	else if (wall_orientation == 'S')
		return (&data->text_img[SOUTH]);
	else if (wall_orientation == 'E')
		return (&data->text_img[EAST]);
	else if (wall_orientation == 'W')
		return (&data->text_img[WEST]);
	return (NULL);
}

/**
 * @brief Adds pixels of a column to the image based on the texture.
 * 
 * @param data Pointer to the main game structure.
 * @param x The x-coordinate of the column.
 * @param wall_config Pointer to the wall configuration structure.
 * @param ray Pointer to the ray structure.
 */
void	add_pixels_col_to_img_txt(t_cub3d *data, int x,
	t_dda *wall_config, t_ray *ray)
{
	int				i;
	t_texture		*texture;
	t_pixel_column	c;

	texture = texture_to_display(data, wall_config->orientation);
	c.tex_x = get_texture_x(ray, wall_config, texture);
	c.height = (int)(data->player.aspect_ratio * 1.5 * (SCREEN_HEIGHT
				/ (wall_config->corrected_dist * FOV / 90.0)));
	c.y_start = (int)((SCREEN_HEIGHT - c.height) * 0.5);
	c.y_end = c.y_start + c.height;
	i = c.y_start;
	while (i < c.y_end)
	{
		c.tex_y = ((i - c.y_start) * texture->y) / c.height;
		c.color = *((int *)(texture->pixels + c.tex_y
					* texture->line_len + c.tex_x
					* (texture->bits_per_pixel / 8)));
		put_pixel(&data->framebuffer, x, i, c.color);
		i++;
	}
	if (SCREEN_WIDTH == 450 && SCREEN_HEIGHT == 932)
		draw_overlay_column(data, x);
}
