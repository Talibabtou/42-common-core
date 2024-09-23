/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:07:34 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/18 13:31:29 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Extracts the index of the texture from a given line in the configuration file.
 * 
 * @param line The line from the configuration file to parse.
 * @return The index of the texture if found, -1 otherwise.
 */
int	get_texture_index_from_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && ft_isspace(line[i + 2]))
		return (NORTH);
	else if (line[i] == 'S' && line[i + 1] == 'O' && ft_isspace(line[i + 2]))
		return (SOUTH);
	else if (line[i] == 'W' && line[i + 1] == 'E' && ft_isspace(line[i + 2]))
		return (WEST);
	else if (line[i] == 'E' && line[i + 1] == 'A' && ft_isspace(line[i + 2]))
		return (EAST);
	else if (line[i] == 'F' && ft_isspace(line[i + 1]))
		return (F);
	else if (line[i] == 'C' && ft_isspace(line[i + 1]))
		return (C);
	else
		free_and_exit_error(ID_TEXT_E);
	return (-1);
}

/**
 * Finds the starting index of the texture path in a given line.
 * 
 * @param line The line from the configuration file to parse.
 * @return The starting index of the texture path if found, -1 otherwise.
 */
static int	find_texture_path_start(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	i += 2;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		free_and_exit_error(TEXT_PATH);
	return (i);
}

/**
 * Checks if a given path has the .xpm extension.
 * 
 * @param path The path to check.
 * @return 0 if the path has the .xpm extension, -1 otherwise.
 */
static int	has_xpm_extension(const char *path)
{
	char	*extension;

	extension = ft_strrchr(path, '.');
	if (!extension || ft_strcmp(extension, ".xpm") != 0)
		free_and_exit_error(TEXT_PATH);
	return (false);
}

/**
 * Extracts the texture path from a given line
 * and saves it to the appropriate texture file.
 * 
 * @param text_path The structure to save the texture path to.
 * @param line The line from the configuration file to parse.
 * @param index_text The index of the texture to save the path for.
 */
void	extract_texture_path(t_text_file *text_path, char *line, int index_text)
{
	int		i;
	char	*path;

	check_double_text(index_text, text_path);
	i = find_texture_path_start(line);
	if (i == -1)
		free_and_exit_error(TEXT_PATH);
	has_xpm_extension(&line[i]);
	test_and_open_file(&line[i]);
	path = ft_gc(ft_strdup(&line[i]));
	if (!path)
		free_and_exit_error(MALLOC_ERR_MSG);
	save_text_path(text_path, index_text, path);
}
