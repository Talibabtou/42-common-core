/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:00:09 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/05 08:17:29 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Checks the command line arguments for validity.
 * 
 * @param argc The number of command line arguments.
 * @param argv The array of command line arguments.
 */
void	args_check(int argc, char **argv)
{
	int	i;

	if (argc != 2)
		print_and_exit_error(E_NB_ARGS);
	if (SCREEN_HEIGHT > MAX_HEIGHT || SCREEN_WIDTH > MAX_WIDTH)
		print_and_exit_error(E_PREPROCESS_MACRO);
	i = ft_strlen(argv[1]) - 4;
	if (ft_strcmp(&argv[1][i], ".cub") != 0)
		print_and_exit_error(FILE_EXTENSION);
}

/**
 * The main entry point of the program.
 * 
 * @param argc The number of command line arguments.
 * @param argv The array of command line arguments.
 * @return The exit status of the program.
 */
int	main(int argc, char **argv)
{
	t_cub3d	*data;

	args_check(argc, argv);
	data = init_struct();
	process_config_and_map(data, argv[1]);
	init_mlx(&data->mlx);
	init_image(data);
	init_sprites(data);
	if (SCREEN_WIDTH == 450 && SCREEN_HEIGHT == 932)
		init_overlay(data);
	init_player(&data->grid, &data->player);
	game_event_loop(data);
	return (false);
}
