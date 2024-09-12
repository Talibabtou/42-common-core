/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:56:42 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/12 19:06:17 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Prints an error message and exits the program
 * 
 * @param msg The error message to print
 */
void	print_and_exit_error(char *msg)
{
	ft_printfd(2, "%s%s%s\n", RED, msg, RESET);
	exit(EXIT_FAILURE);
}

/**
 * @brief Frees resources, prints an error message and exits the program
 * 
 * @param msg The error message to print
 */
void	free_and_exit_error(char *msg)
{
	ft_printfd(2, "%s%s%s", RED, msg, RESET);
	clear_gc();
	exit(EXIT_FAILURE);
}

/**
 * @brief Closes the program, freeing resources and exiting with a specified code
 *
 * @param cub3d Pointer to the main program structure
 * @param msg Error message to display (can be NULL if no message is needed)
 * @param exit_code The exit code to use when terminating the program
 */
void	close_program(t_cub3d *cub3d, char *msg, int exit_code)
{
	int	i;

	i = 0;
	if (msg)
		ft_printfd(2, "%s%s%s\n", RED, msg, RESET);
	if (cub3d->framebuffer.img_ptr)
		mlx_destroy_image(cub3d->mlx.mlx_ptr, cub3d->framebuffer.img_ptr);
	while (i < 4)
	{
		if (cub3d->text_img[i].reference)
			mlx_destroy_image(cub3d->mlx.mlx_ptr, cub3d->text_img[i].reference);
		i++;
	}
	if (SCREEN_WIDTH == 450 && SCREEN_HEIGHT == 932 && cub3d->overlay.img)
		mlx_destroy_image(cub3d->mlx.mlx_ptr, cub3d->overlay.img);
	if (cub3d->mlx.win_ptr)
		mlx_destroy_window(cub3d->mlx.mlx_ptr, cub3d->mlx.win_ptr);
	if (cub3d->mlx.mlx_ptr)
		mlx_destroy_display(cub3d->mlx.mlx_ptr);
	clear_gc();
	exit(exit_code);
}
