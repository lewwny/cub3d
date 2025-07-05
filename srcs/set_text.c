/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:46:01 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/05 17:50:37 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_texture(t_game *game)
{
	t_ray	*ray;

	ray = &game->player.ray;
	if (ray->side == NO_SO)
		ray->wall.wall_x = ray->ray_y;
	else
		ray->wall.wall_x = ray->ray_x;
	ray->wall.wall_x -= floor(ray->wall.wall_x);
	ray->wall.step = 1.0 * 64 / ray->wall.height;
	ray->wall.tex_pos = (ray->wall.start - HEIGHT / 2
			+ ray->wall.height / 2) * ray->wall.step;
}
