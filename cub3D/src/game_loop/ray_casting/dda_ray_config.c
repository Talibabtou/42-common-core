/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_ray_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:57:24 by gdumas            #+#    #+#             */
/*   Updated: 2024/09/04 15:29:51 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Initializes the ray configuration for DDA ray casting.
 * 
 * @param camera_x The camera's x position.
 * @param player Pointer to the player structure.
 * @param ray Pointer to the ray structure.
 */
void	init_ray(const double camera_x, t_player *player, t_ray *ray)
{
	ray->true_pos.x = player->pos.x;
	ray->true_pos.y = player->pos.y;
	ray->grid_pos.x = (int)player->pos.x;
	ray->grid_pos.y = (int)player->pos.y;
	ray->dir.x = player->dir.x + player->plane.x * camera_x;
	ray->dir.y = player->dir.y + player->plane.y
		* camera_x / player->aspect_ratio;
}

/**
 * @brief Configures the ray for DDA (Digital Differential Analyzer) algorithm.
 * 
 * @param r Pointer to the ray structure.
 */
void	get_ray_config_dda(t_ray *r)
{
	r->delta_dist.x = fabs(1 / r->dir.x);
	r->delta_dist.y = fabs(1 / r->dir.y);
	if (r->dir.x < 0)
	{
		r->step_direction.x = -1;
		r->side_dist.x = (r->true_pos.x - r->grid_pos.x) * r->delta_dist.x;
	}
	else
	{
		r->step_direction.x = 1;
		r->side_dist.x = (r->grid_pos.x - r->true_pos.x + 1) * r->delta_dist.x;
	}
	if (r->dir.y < 0)
	{
		r->step_direction.y = -1;
		r->side_dist.y = (r->true_pos.y - r->grid_pos.y) * r->delta_dist.y;
	}
	else
	{
		r->step_direction.y = 1;
		r->side_dist.y = (r->grid_pos.y - r->true_pos.y + 1) * r->delta_dist.y;
	}
}
