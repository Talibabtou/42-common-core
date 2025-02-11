/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:58:14 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/12 18:56:47 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Checks if a given line is empty.
 * 
 * @param line The line to check.
 * @return 1 if the line is empty, 0 otherwise.
 */
static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (false);
		i++;
	}
	return (true);
}

/**
 * Parses lines related to textures and colors.
 * 
 * @param data The data structure to store the parsed information.
 * @param file The array of lines to parse.
 * @return The index of the last processed line.
 */
static int	parse_texture_and_color_lines(t_cub3d *data, char **file)
{
	int	i;
	int	index_text;
	int	line_nbr;

	i = -1;
	line_nbr = 0;
	while (file[++i] && line_nbr < 6)
	{
		if (is_empty_line(file[i]))
			i++;
		else
		{
			index_text = get_texture_index_from_line(file[i]);
			if (index_text == F || index_text == C)
				extract_color(&data->colors, file[i], index_text);
			else
				extract_texture_path(&data->text_path, file[i], index_text);
			line_nbr++;
		}
	}
	if (file[i] == NULL || line_nbr != 6)
		free_and_exit_error(SYNTAX_LINE);
	return (i);
}

/**
 * Processes the configuration and map data from a file.
 * 
 * @param data The data structure to store the parsed information.
 * @param file The file content to process.
 */
void	process_config_and_map(t_cub3d *data, char *file)
{
	int		i;
	char	**data_file;

	data_file = ft_gc(extract_file(file));
	if (!data_file)
		free_and_exit_error(MALLOC_ERR_MSG);
	data->text_path.text = ft_gc(ft_calloc(4, sizeof(char **)));
	if (!data->text_path.text)
		free_and_exit_error(MALLOC_ERR_MSG);
	i = parse_texture_and_color_lines(data, data_file);
	extract_grid(&data->grid, &data_file[i]);
}
