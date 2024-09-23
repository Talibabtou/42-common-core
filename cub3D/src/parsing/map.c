/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:58:04 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/17 16:39:17 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Checks if the map's character set is valid.
 * 
 * @param map The map to check.
 * @return True if the map's character set is valid, false otherwise.
 */
bool	is_map_charset_valid(char **map)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	player_charset_nbr;

	player_charset_nbr = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr("NSEW", map[y][x]))
				player_charset_nbr++;
			else if (!ft_strchr("01 ", map[y][x]))
				return (false);
			x++;
		}
		y++;
	}
	return (player_charset_nbr == 1);
}

/**
 * @brief Checks if the extreme lines of the map are valid.
 * 
 * @param line The line to check.
 * @return True if the line is valid, false otherwise.
 */
bool	extrem_lines_are_valid(const char *line)
{
	while (*line)
	{
		if (!ft_strchr("1 ", *line))
			return (false);
		line++;
	}
	return (true);
}

/**
 * @brief Checks if the map is enclosed by walls.
 * 
 * @param grid The map to check.
 * @param height The height of the map.
 * @return True if the map is enclosed by walls, false otherwise.
 */
bool	is_map_enclosed_by_walls(char **grid, unsigned int height)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	y = 0;
	while (grid[y] && y < height)
	{
		while (grid[y][x])
		{
			if ((x == 0 && grid[y][x] != '1'
				&& grid[y][x] != ' ')
				|| is_space_line(grid[y]))
				return (false);
			if (is_char_adjacent_to_space(grid, x, y))
				return (false);
			x++;
		}
		x = 0;
		y++;
	}
	return (true);
}

/**
 * @brief Allocates memory for the grid and copies
 * the content from the input grid.
 * @param grid_in_file The input grid to copy from.
 * @param height The height of the grid.
 * @return A pointer to the newly allocated and copied grid.
 */
static char	**allocate_and_copy_grid(char **grid_in_file, int height)
{
	char	**ret_map;
	int		i;

	ret_map = ft_gc(ft_calloc(height + 1, sizeof(char *)));
	if (!ret_map)
		free_and_exit_error(MALLOC_ERR_MSG);
	i = 0;
	while (grid_in_file[i])
	{
		ret_map[i] = ft_gc(ft_strdup(grid_in_file[i]));
		if (!ret_map[i])
			free_and_exit_error(MALLOC_ERR_MSG);
		i++;
	}
	ret_map[i] = NULL;
	return (ret_map);
}

/**
 * @brief Extracts the grid from the map.
 * 
 * @param grid Pointer to the t_grid structure to store the extracted grid.
 * @param grid_in_file The map to extract the grid from.
 */
void	extract_grid(t_grid *grid, char **grid_in_file)
{
	int		height;
	char	**ret_map;

	height = 0;
	while (grid_in_file[height])
	{
		height++;
		if (height > MAX_HEIGHT)
			free_and_exit_error(SIZE_ERROR_GRID);
	}
	if (!is_valid_map(grid_in_file, height))
		free_and_exit_error(MAP_ERROR);
	ret_map = allocate_and_copy_grid(grid_in_file, height);
	grid->height = height;
	grid->width = get_max_width_grid(ret_map);
	grid->content = ret_map;
}
