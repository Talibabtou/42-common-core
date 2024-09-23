/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:57:59 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/16 11:41:23 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Tests if a file can be opened and closes it.
 * 
 * @param file The path to the file to be tested.
 */
void	test_and_open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		free_and_exit_error(FILE_PATH);
	close(fd);
}

/**
 * @brief Calculates the size of a file.
 * 
 * @param file The path to the file whose size is to be calculated.
 * @return The size of the file in characters.
 */
static int	get_size_file(char *file)
{
	int		fd;
	int		size;
	char	buffer[1024];
	int		bytes_read;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		free_and_exit_error(FILE_PATH);
	size = 0;
	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		size += bytes_read;
		bytes_read = read(fd, buffer, sizeof(buffer));
	}
	if (bytes_read < 0)
		free_and_exit_error(READ_ERROR);
	close(fd);
	return (size);
}

/**
 * @brief Reads the content of a file into a string.
 * 
 * @param file The path to the file whose content is to be read.
 * @return A string containing the content of the file.
 */
static char	*file_to_str(char *file)
{
	char	*file_data;
	int		fd;
	int		i;
	int		size;

	size = get_size_file(file);
	file_data = ft_gc(ft_calloc(size + 1, sizeof(char)));
	if (!file_data)
		free_and_exit_error(MALLOC_ERR_MSG);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		free_and_exit_error(MALLOC_ERR_MSG);
	i = 0;
	while (read(fd, &file_data[i], 1))
		i++;
	file_data[i] = '\0';
	close(fd);
	return (file_data);
}

/**
 * @brief Checks if a map in a file has an empty line.
 * 
 * @param str_file The string representation of the file content.
 * @return True if the map has an empty line, false otherwise.
 */
bool	map_has_empty_line(char *str_file)
{
	char	*map;

	map = ft_strtrim(&str_file[find_start_map(str_file)], "\n");
	if (!map)
		free_and_exit_error(MALLOC_ERR_MSG);
	add_to_gc(map);
	while (*map)
	{
		if (!ft_strncmp(map, "\n\n", 2))
			return (true);
		map++;
	}
	del_one_gc(map);
	return (false);
}

/**
 * @brief Extracts the content of a file into an array of strings.
 * 
 * @param file The path to the file whose content is to be extracted.
 * @return An array of strings containing the content of the file.
 */
char	**extract_file(char *file)
{
	char	*file_str;
	char	**split_file;

	file_str = file_to_str(file);
	if (map_has_empty_line(file_str))
		free_and_exit_error(MAP_LINE_BREAK);
	split_file = ft_gc(ft_split(file_str, '\n'));
	if (!split_file)
		free_and_exit_error(MALLOC_ERR_MSG);
	del_one_gc(file_str);
	return (split_file);
}
