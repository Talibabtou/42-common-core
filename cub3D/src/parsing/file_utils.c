/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:36:37 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/05 08:13:06 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Checks if a character is part of the set of characters used to identify
 * specific sections in the configuration file.
 * 
 * @param c The character to check.
 * @return true if the character is part of the set, false otherwise.
 */
static bool	is_charset_txt(char c)
{
	return (c == 'F' || c == 'C' || c == 'S'
		|| c == 'W' || c == 'E' || c == 'N');
}

/**
 * Finds the starting position of the map in the configuration file.
 * 
 * @param str_file The string representation of the configuration file.
 * @return The starting position of the map in the configuration file.
 */
int	find_start_map(char *str_file)
{
	int	start;
	int	line;

	start = 0;
	line = 0;
	while (str_file[start] && line < 6)
	{
		if (str_file[start] == '\n')
		{
			line++;
			while (str_file[start] == '\n')
				start++;
		}
		else
			start++;
	}
	if (is_charset_txt(str_file[start + 1]))
		free_and_exit_error(CONFIG_ERROR);
	return (start);
}
