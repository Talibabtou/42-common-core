/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:37:11 by mcombeau          #+#    #+#             */
/*   Updated: 2024/02/13 19:06:16 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

inline int	mandelbrot(double cr, double ci)
{
	register int	n;
	register double	zr;
	register double	zi;
	register double	tmp;

	zr = 0;
	zi = 0;
	n = 0;
	while (n < MAX_ITERATIONS)
	{
		if ((zr * zr + zi * zi) > 4.0)
			break ;
		tmp = 2 * zr * zi + ci;
		zr = zr * zr - zi * zi + cr;
		zi = tmp;
		n++;
	}
	return (n);
}
