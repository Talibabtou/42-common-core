/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:07:34 by gemartel          #+#    #+#             */
/*   Updated: 2024/08/20 17:16:27 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	find_texture_path_start(const char *line)
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

int	has_xpm_extension(const char *path)
{
	char	*extension;

	extension = ft_strrchr(path, '.');
	if (ft_strcmp(extension, ".xpm") != 0)
		free_and_exit_error(TEXT_PATH);
	return (0);
}

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
	path = strdup_gc(&line[i], TEXTURE);
	if (!path)
		free_and_exit_error(MALLOC_ERR_MSG);
	save_text_path(text_path, index_text, path);
}
