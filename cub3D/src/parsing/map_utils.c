/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:58:09 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/05 11:27:08 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Checks if a line is a space line.
 * 
 * @param str The line to check.
 * @return True if the line is a space line, false otherwise.
 */
bool	is_space_line(const char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (false);
		str++;
	}
	return (true);
}

/**
 * @brief Gets the height of the grid.
 * 
 * @param grid The grid to get the height of.
 * @return The height of the grid.
 */
int	get_height_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
		i++;
	if (i > MAX_HEIGHT)
		free_and_exit_error(SIZE_ERROR_GRID);
	return (i);
}

/**
 * @brief Gets the maximum width of the grid.
 * 
 * @param grid The grid to get the maximum width of.
 * @return The maximum width of the grid.
 */
int	get_max_width_grid(char **grid)
{
	int	i;
	int	width;
	int	tmp;

	i = 0;
	width = 0;
	while (grid[i])
	{
		tmp = ft_strlen(grid[i]) - 1;
		while (ft_isspace(grid[i][tmp]))
			tmp--;
		if (tmp > width)
			width = tmp;
		i++;
	}
	if (width > MAX_WIDTH)
		free_and_exit_error(SIZE_ERROR_GRID);
	return (width);
}

/**
 * @brief Checks if a character is adjacent to a space in the map.
 * 
 * @param map The map to check.
 * @param x The x coordinate of the character.
 * @param y The y coordinate of the character.
 * @return True if the character is adjacent to a space, false otherwise.
 */
bool	is_char_adjacent_to_space(char **map, int x, int y)
{
	char c = map[y][x];

	if (c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != 'D')
		return (false);
	if (map[y][x + 1] == ' ' || map[y][x + 1] == '\0' ||
		map[y][x - 1] == ' ' ||
		map[y + 1][x] == ' ' || map[y + 1][x] == '\0' ||
		map[y - 1][x] == ' ' || map[y - 1][x] == '\0')
		return (true);

	return (false);
}

/**
 * @brief Checks if the map is valid.
 * 
 * @param grid The map to check.
 * @param height The height of the map.
 * @return True if the map is valid, false otherwise.
 */
bool	is_valid_map(char **grid, int height)
{
	if (!extrem_lines_are_valid(grid[0])
		|| !extrem_lines_are_valid(grid[height - 1]))
		return (false);
	if (!is_map_enclosed_by_walls(grid, height) || !is_map_charset_valid(grid))
		return (false);
	return (true);
}