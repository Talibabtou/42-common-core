/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:57:53 by gemartel          #+#    #+#             */
/*   Updated: 2024/08/20 17:16:01 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	index_code_color(const char *line_color)
{
	int	i;

	i = 0;
	while (line_color[i] && ft_isspace(line_color[i]))
		i++;
	if (line_color[i] != 'F' && line_color[i] != 'C')
		free_and_exit_error(COLOR_FORMAT_ERROR);
	i++;
	while (line_color[i] && ft_isspace(line_color[i]))
		i++;
	if (!ft_isdigit(line_color[i]))
		free_and_exit_error(COLOR_FORMAT_ERROR);
	return (i);
}

static bool	is_int_overflow(char *str_nbr)
{
	int		sign;
	size_t	str_len;

	str_len = ft_strlen(str_nbr);
	if (str_nbr[0] == '-')
		sign = -1;
	else
		sign = 1;
	if ((sign < 0 && str_len > 11) || (sign > 0 && str_len > 10))
		return (true);
	else if ((sign < 0 && str_len < 11) || (sign > 0 && str_len < 10))
		return (false);
	if ((sign < 0 && ft_strcmp(str_nbr, "-2147483648") > 0)
		|| (sign > 0 && ft_strcmp(str_nbr, "2147483647") > 0))
		return (true);
	return (false);
}

void	check_format_color(char *line, int start)
{
	int	i;
	int	nbr_comma;

	nbr_comma = 0;
	i = start;
	while (line[i])
	{
		if (line[i] != ',' && !ft_isdigit(line[i]))
			free_and_exit_error(COLOR_FORMAT_ERROR);
		else if (line[i] == ',')
			nbr_comma++;
		i++;
	}
	if (nbr_comma != 2)
		free_and_exit_error(COLOR_FORMAT_ERROR);
}

void	extract_color(t_colors *colors, char *line, int index_color)
{
	int		i;
	char	**color;
	int		rgb[3];

	check_double_color(colors, index_color);
	i = index_code_color(line);
	check_format_color(line, i);
	color = split_gc(&line[i], ',', TMP);
	if (!color)
		free_and_exit_error(MALLOC_ERR_MSG);
	i = -1;
	while (++i < 3)
	{
		if (!color[i])
			free_and_exit_error(COLOR_FORMAT_ERROR);
		if (is_int_overflow(color[i]))
			free_and_exit_error(COLOR_FORMAT_ERROR);
		rgb[i] = ft_atoi(color[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			free_and_exit_error(COLOR_FORMAT_ERROR);
	}
	save_color(colors, rgb, index_color);
}
