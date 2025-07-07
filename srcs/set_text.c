/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:46:01 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/07 17:03:02 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_texture(t_game *game, double raydirx, double raydiry)
{
	t_ray		*ray;
	t_player	*player;

	ray = &game->player.ray;
	player = &game->player;
	if (ray->side == NO_SO)
		ray->wall.wall_x = player->posy + ray->distance * raydiry;
	else
		ray->wall.wall_x = player->posx + ray->distance * raydirx;
	ray->wall.wall_x -= floor(ray->wall.wall_x);
	ray->wall.tex_x = (int)(ray->wall.wall_x
			* (double)game->texture.tex_ptr[ray->wall.side].width);
	if (ray->side == NO_SO && raydirx > 0)
		ray->wall.tex_x = game->texture.tex_ptr[ray->wall.side].width
			- ray->wall.tex_x - 1;
	if (ray->side == WE_EA && raydiry < 0)
		ray->wall.tex_x = game->texture.tex_ptr[ray->wall.side].width
			- ray->wall.tex_x - 1;
	ray->wall.step = 1.0 * game->texture.tex_ptr[ray->wall.side].height
		/ ray->wall.height;
	ray->wall.tex_pos = ray->wall.step * (ray->wall.start - HEIGHT / 2
			+ ray->wall.height / 2 - game->player.pitch);
}
