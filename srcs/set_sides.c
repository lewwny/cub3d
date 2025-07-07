/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sides.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:30:45 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/04 13:45:53 by macauchy         ###   ########.fr       */
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
	t_ray	*ray;

	ray = &game->player.ray;
	if (ray->wall.side == NORTH)
		game->buf[y * WIDTH + x] = 0xFF0000;
	else if (ray->wall.side == SOUTH)
		game->buf[y * WIDTH + x] = 0x00FF00;
	else if (ray->wall.side == WEST)
		game->buf[y * WIDTH + x] = 0x0000FF;
	else if (ray->wall.side == EAST)
		game->buf[y * WIDTH + x] = 0xFFFF00;
}
