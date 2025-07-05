/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sides.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:30:45 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/05 17:43:49 by lenygarcia       ###   ########.fr       */
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

// void	color_sides(t_game *game, int x, int y)
// {
// 	t_ray	*ray;

// 	ray = &game->player.ray;
// 	if (ray->wall.side == NORTH)
// 		game->buf[y * WIDTH + x] = 0xFF0000;
// 	else if (ray->wall.side == SOUTH)
// 		game->buf[y * WIDTH + x] = 0x00FF00;
// 	else if (ray->wall.side == WEST)
// 		game->buf[y * WIDTH + x] = 0x0000FF;
// 	else if (ray->wall.side == EAST)
// 		game->buf[y * WIDTH + x] = 0xFFFF00;
// }

void	color_sides(t_game *game, int x, int y)
{
	t_ray			*ray;
	unsigned int	*tex;

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
	int texY = (int)(ray->wall.tex_pos) & (64 - 1);
	ray->wall.tex_pos += ray->wall.step;
	int texX = (int)(ray->wall.wall_x * 64);
	if (ray->wall.side == NORTH || ray->wall.side == SOUTH)
		texX = 64 - texX - 1;
	game->buf[y * WIDTH + x] = tex[texY * 64 + texX];
}
