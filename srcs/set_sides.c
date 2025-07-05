/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sides.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:30:45 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/05 18:56:13 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_sides(t_game *game)
{
	t_ray	*ray;

	ray = &game->player.ray;
	if (!ray->hit)
		return ;
	if (ray->side == WE_EA)
	{
		if (ray->step_size_y > 0)
			ray->wall.side = SOUTH;
		else
			ray->wall.side = NORTH;
	}
	else if (ray->side == NO_SO)
	{
		if (ray->step_size_x > 0)
			ray->wall.side = EAST;
		else
			ray->wall.side = WEST;
	}
}

void	color_sides(t_game *game, int x, int y)
{
	t_ray			*ray;
	unsigned int	*tex;
	int				tex_y;
	int				tex_x;

	tex = NULL;
	ray = &game->player.ray;
	if (ray->wall.side == NORTH)
		tex = game->texture.no_data;
	else if (ray->wall.side == SOUTH)
		tex = game->texture.so_data;
	else if (ray->wall.side == WEST)
		tex = game->texture.we_data;
	else if (ray->wall.side == EAST)
		tex = game->texture.ea_data;
	tex_y = (int)(ray->wall.tex_pos) & (64 - 1);
	ray->wall.tex_pos += ray->wall.step;
	tex_x = (int)(ray->wall.wall_x * 64);
	if (ray->wall.side == NORTH || ray->wall.side == SOUTH)
		tex_x = 64 - tex_x - 1;
	game->buf[y * WIDTH + x] = tex[tex_y * 64 + tex_x];
}
