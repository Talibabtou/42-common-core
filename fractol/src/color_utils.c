/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:53:25 by gdumas            #+#    #+#             */
/*   Updated: 2024/02/13 19:24:00 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

inline int	get_percent_color(int color, double percent)
{
	int		rgb[3];
	int		trgb[3];
	double	percentage;

	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = (color >> 0) & 0xFF;
	percentage = (percent / 100) * 256;
	trgb[0] = (rgb[0] + percentage) - 256;
	trgb[1] = (rgb[1] + percentage) - 256;
	trgb[2] = (rgb[2] + percentage) - 256;
	return (0xFF << 24 | trgb[0] << 16 | trgb[1] << 8 | trgb[2]);
}

inline int	interpolate(int startcolor, int endcolor, double fraction)
{
	int	start_rgb[3];
	int	end_rgb[3];
	int	interp_rgb[3];

	start_rgb[0] = ((startcolor >> 16) & 0xFF);
	start_rgb[1] = ((startcolor >> 8) & 0xFF);
	start_rgb[2] = ((startcolor >> 0) & 0xFF);
	end_rgb[0] = ((endcolor >> 16) & 0xFF);
	end_rgb[1] = ((endcolor >> 8) & 0xFF);
	end_rgb[2] = ((endcolor >> 0) & 0xFF);
	interp_rgb[0] = start_rgb[0] + fraction * (end_rgb[0] - start_rgb[0]);
	interp_rgb[1] = start_rgb[1] + fraction * (end_rgb[1] - start_rgb[1]);
	interp_rgb[2] = start_rgb[2] + fraction * (end_rgb[2] - start_rgb[2]);
	return (0xFF << 24 | interp_rgb[0] << 16
		| interp_rgb[1] << 8 | interp_rgb[2]);
}
