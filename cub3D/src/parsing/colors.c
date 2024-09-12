/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:57:53 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/12 18:32:48 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Finds the index of the color code in the line.
 * 
 * @param line_color The line containing the color code.
 * @return The index of the color code in the line.
 */
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

/**
 * @brief Checks the format of the color in the line.
 * 
 * @param line The line containing the color.
 * @param start The index to start checking from.
 */
void	check_format_color(char *line, int start)
{
	int	i;
	int	nbr_comma;

	nbr_comma = 0;
	i = start;
	while (line[i])
	{
		if (line[i] != ',' && !ft_isdigit(line[i]) && !ft_isspace(line[i]))
			free_and_exit_error(COLOR_FORMAT_ERROR);
		if (line[i] == ',')
		{
			nbr_comma++;
			i++;
			while (line[i] && ft_isspace(line[i]))
				i++;
			if (!ft_isdigit(line[i]))
				free_and_exit_error(COLOR_FORMAT_ERROR);
		}
		else
			i++;
	}
	if (nbr_comma != 2)
		free_and_exit_error(COLOR_FORMAT_ERROR);
}

/**
 * @brief Extracts the color from the line and saves it.
 * 
 * @param colors Pointer to the t_colors structure containing color information.
 * @param line The line containing the color.
 * @param index_color The index indicating whether
 * to save the color for the floor (4) or ceiling (other).
 */
void	extract_color(t_colors *colors, char *line, int index_color)
{
	int		i;
	char	**color;
	int		rgb[3];
	char	*endptr;

	check_double_color(colors, index_color);
	i = index_code_color(line);
	check_format_color(line, i);
	color = ft_gc(ft_split(&line[i], ','));
	if (!color)
		free_and_exit_error(MALLOC_ERR_MSG);
	i = 0;
	while (i < 3)
	{
		if (!color[i])
			free_and_exit_error(COLOR_FORMAT_ERROR);
		rgb[i] = ft_strtol(color[i], &endptr, 10);
		while (ft_isspace(*endptr))
			endptr++;
		if (*endptr != '\0' || rgb[i] < 0 || rgb[i] > 255)
			free_and_exit_error(COLOR_FORMAT_ERROR);
		i++;
	}
	save_color(colors, rgb, index_color);
}
