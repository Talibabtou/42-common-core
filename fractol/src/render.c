/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:15:19 by gdumas            #+#    #+#             */
/*   Updated: 2024/02/14 11:21:44 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

inline static void	set_pixel_color(t_fractol *f, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		f->buf[x * 4 + y * WIDTH * 4] = color;
		f->buf[x * 4 + y * WIDTH * 4 + 1] = color >> 8;
		f->buf[x * 4 + y * WIDTH * 4 + 2] = color >> 16;
	}
}

inline static int	calculate_fractal(t_fractol *f, double pr, double pi)
{
	register int	nb_iter;

	nb_iter = 0;
	if (f->set == MANDELBROT)
		nb_iter = mandelbrot(pr, pi);
	else if (f->set == JULIA)
		nb_iter = julia(f, pr, pi);
	else if (f->set == BURNING_SHIP)
		nb_iter = burning_ship(pr, pi);
	return (nb_iter);
}

inline void	render(t_fractol *f)
{
	register int		x;
	register int		y;
	register double		pr;
	register double		pi;
	register int		nb_iter;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pr = f->min_r + (double)x * (f->max_r - f->min_r) / WIDTH;
			pi = f->max_i + (double)y * (f->min_i - f->max_i) / HEIGHT;
			nb_iter = calculate_fractal(f, pr, pi);
			set_pixel_color(f, x, y, f->palette[nb_iter]);
		}
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
