/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:58:09 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/16 18:10:23 by gdumas           ###   ########.fr       */
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

static bool	check_vertical_adjacent(char *line, int x)
{
	int	i;

	i = 0;
	while (line[i] && i < x)
		i++;
	return (i == x && (line[i] == ' ' || line[i] == '\0'));
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
	char	c;

	if (!map || !map[y] || x < 0 || y < 0)
		return (false);
	c = map[y][x];
	if (c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != 'D')
		return (false);
	if (map[y][x + 1] == ' ' || map[y][x + 1] == '\0')
		return (true);
	if (x > 0 && map[y][x - 1] == ' ')
		return (true);
	if (map[y + 1] && check_vertical_adjacent(map[y + 1], x))
		return (true);
	if (y > 0 && map[y - 1] && check_vertical_adjacent(map[y - 1], x))
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
