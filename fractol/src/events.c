/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:49:23 by gdumas            #+#    #+#             */
/*   Updated: 2024/02/14 15:50:20 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	zoom(t_fractol *f, double zoom)
{
	double	range_r;
	double	range_i;

	range_r = f->min_r - f->max_r;
	range_i = f->max_i - f->min_i;
	f->max_r = f->max_r + (range_r - zoom * range_r) * 0.5;
	f->min_r = f->max_r + zoom * range_r;
	f->min_i = f->min_i + (range_i - zoom * range_i) * 0.5;
	f->max_i = f->min_i + zoom * range_i;
}

static void	move(t_fractol *f, double distance, char direction)
{
	double	range_r;
	double	range_i;

	range_r = f->max_r - f->min_r;
	range_i = f->max_i - f->min_i;
	if (direction == 'R')
	{
		f->min_r += range_r * distance;
		f->max_r += range_r * distance;
	}
	else if (direction == 'L')
	{
		f->min_r -= range_r * distance;
		f->max_r -= range_r * distance;
	}
	else if (direction == 'D')
	{
		f->min_i -= range_i * distance;
		f->max_i -= range_i * distance;
	}
	else if (direction == 'U')
	{
		f->min_i += range_i * distance;
		f->max_i += range_i * distance;
	}
}

static int	key_event_extend(int keycode, t_fractol *mlx)
{
	if (keycode == KEY_ONE && mlx->set != MANDELBROT)
		mlx->set = MANDELBROT;
	else if (keycode == KEY_TWO && mlx->set != JULIA)
		mlx->set = JULIA;
	else if (keycode == KEY_THREE && mlx->set != BURNING_SHIP)
		mlx->set = BURNING_SHIP;
	else
		return (1);
	get_complex_layout(mlx);
	return (render(mlx), 0);
}

int	key_event(int keycode, t_fractol *mlx)
{
	if (keycode == KEY_ESC)
	{
		end_fractol(mlx);
		return (0);
	}
	else if (keycode == KEY_PLUS)
		zoom(mlx, 0.5);
	else if (keycode == KEY_MINUS)
		zoom(mlx, 2);
	else if (keycode == KEY_UP || keycode == KEY_W)
		move(mlx, 0.2, 'U');
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		move(mlx, 0.2, 'D');
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		move(mlx, 0.2, 'L');
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		move(mlx, 0.2, 'R');
	else if (keycode == KEY_SPACE)
		color_shift(mlx);
	else if (!key_event_extend(keycode, mlx))
		return (1);
	else
		return (1);
	return (render(mlx), 0);
}

int	mouse_event(int keycode, int x, int y, t_fractol *mlx)
{
	if (keycode == MOUSE_WHEEL_UP)
	{
		zoom(mlx, ZOOM);
		x -= WIDTH * 0.5;
		y -= HEIGHT * 0.5;
		if (x < 0)
			move(mlx, (double)x * -1 / WIDTH, 'L');
		else if (x > 0)
			move(mlx, (double)x / WIDTH, 'R');
		if (y < 0)
			move(mlx, (double)y * -1 / HEIGHT, 'U');
		else if (y > 0)
			move (mlx, (double)y / HEIGHT, 'D');
	}
	else if (keycode == MOUSE_WHEEL_DOWN)
		zoom(mlx, 1 / ZOOM);
	else if (keycode == MOUSE_BTN)
	{
		if (mlx->set == JULIA)
			julia_shift(x, y, mlx);
	}
	else
		return (0);
	return (render(mlx), 0);
}
