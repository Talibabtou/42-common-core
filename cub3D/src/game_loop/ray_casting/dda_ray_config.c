/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_ray_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:46:48 by bboissen          #+#    #+#             */
/*   Updated: 2024/09/17 13:03:04 by bboissen         ###   ########.fr       */
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
void	init_ray(const double angle, t_player *player, t_ray *ray)
{
	ray->head_pos.x = player->pos.x;
	ray->head_pos.y = player->pos.y;
	ray->grid_pos.x = (int)player->pos.x;
	ray->grid_pos.y = (int)player->pos.y;
	ray->dir.x = cos(angle);
	ray->dir.y = sin(angle);
}

/**
 * @brief Configures the ray for DDA (Digital Differential Analyzer) algorithm.
 *  This determines the direction of movement along the axis and calculates 
 *  the initial distance to the nearest side of a grid cell
 * @param r Pointer to the ray structure.
 */
void	get_ray_config_dda(t_ray *r)
{
	r->delta_dist.x = fabs(1 / r->dir.x);
	r->delta_dist.y = fabs(1 / r->dir.y);
	if (r->dir.x < 0)
	{
		r->step_direction.x = -1;
		r->side_dist.x = (r->head_pos.x - r->grid_pos.x) * r->delta_dist.x;
	}
	else
	{
		r->step_direction.x = 1;
		r->side_dist.x = (r->grid_pos.x - r->head_pos.x + 1) * r->delta_dist.x;
	}
	if (r->dir.y < 0)
	{
		r->step_direction.y = -1;
		r->side_dist.y = (r->head_pos.y - r->grid_pos.y) * r->delta_dist.y;
	}
	else
	{
		r->step_direction.y = 1;
		r->side_dist.y = (r->grid_pos.y - r->head_pos.y + 1) * r->delta_dist.y;
	}
}
