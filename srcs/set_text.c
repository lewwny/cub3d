/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:46:01 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/04 17:36:28 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_texture(t_game *game)
{
	t_ray		*ray;
	t_player	*player;

	ray = &game->player.ray;
	player = &game->player;
	if (ray->side == NO_SO)
		ray->wall.wall_x = player->posy + ray->distance * ray->ray_y;
	else
		ray->wall.wall_x = player->posx + ray->distance * ray->ray_x;
	ray->wall.wall_x -= floor(ray->wall.wall_x);
	ray->wall.step = 1.0 * 64 / ray->wall.height;
	ray->wall.step /= 4;
	ray->wall.tex_pos = ray->wall.step * (ray->wall.start - HEIGHT / 2 + ray->wall.height / 2);
}
