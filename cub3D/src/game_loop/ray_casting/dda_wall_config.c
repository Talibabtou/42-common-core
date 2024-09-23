/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_wall_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:46:54 by bboissen          #+#    #+#             */
/*   Updated: 2024/09/17 15:52:12 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Checks if a wall is detected at the current ray position.
 * 
 * @param grid Pointer to the grid structure.
 * @param ray Pointer to the ray structure.
 * @return True if a wall is detected, false otherwise.
 */
static bool	is_wall_detected(const t_grid *grid, const t_ray *ray)
{
	return (grid->content[ray->grid_pos.y][ray->grid_pos.x] == '1');
}

/**
 * @brief Calculates the perpendicular distance to the wall.
 * 
 * @param last_side_tested The last side tested ('x' or 'y').
 * @param ray Pointer to the ray structure.
 * @return The perpendicular distance to the wall.
 */
static double	process_wall_dist(char last_side_tested, const t_ray *ray)
{
	double	perp_wall_dist;

	if (last_side_tested == 'x')
		perp_wall_dist = (ray->grid_pos.x - ray->head_pos.x
				+ (1 - ray->step_direction.x) * 0.5) / ray->dir.x;
	else
		perp_wall_dist = (ray->grid_pos.y - ray->head_pos.y
				+ (1 - ray->step_direction.y) * 0.5) / ray->dir.y;
	return (perp_wall_dist);
}

/**
 * @brief Determines the orientation of the wall.
 * 
 * @param ray Pointer to the ray structure.
 * @param last_side_tested The last side tested ('x' or 'y').
 * @return The orientation of the wall ('N', 'S', 'E', or 'W').
 */
static char	process_wall_orientation(const t_ray *ray, char last_side_tested)
{
	if (last_side_tested == 'x')
	{
		if (ray->dir.x > 0)
			return ('E');
		else
			return ('W');
	}
	else
	{
		if (ray->dir.y > 0)
			return ('N');
		else
			return ('S');
	}
}

/**
 * @brief Configures the wall configuration using DDA.
 * 
 * @param grid Pointer to the grid structure.
 * @param ray Pointer to the ray structure.
 * @param wall_config Pointer to the wall configuration structure.
 */
void	get_wall_config_dda(const t_grid *grid, t_ray *ray,
	t_dda *wall_config, double ray_angle)
{
	bool	hit;
	char	last_side_tested;

	hit = false;
	while (!hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->grid_pos.x += ray->step_direction.x;
			last_side_tested = 'x';
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->grid_pos.y += ray->step_direction.y;
			last_side_tested = 'y';
		}
		hit = is_wall_detected(grid, ray);
	}
	wall_config->dist = process_wall_dist(last_side_tested, ray);
	wall_config->corrected_dist = wall_config->dist * cos(ray_angle);
	wall_config->orientation = process_wall_orientation(ray, last_side_tested);
}
