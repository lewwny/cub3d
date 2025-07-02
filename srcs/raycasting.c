/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:51:23 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/02 17:59:37 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_vertical_line(t_game *data, int x, int start, int end, int color)
{
	int	y;

	y = start;
	while (y <= end)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
		y++;
	}
}

void	raycasting(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		game->player.ray.camera_x = 2 * x / (double)WIDTH - 1;
		game->player.ray.raydirx = game->player.dirx
			+ game->player.planex * game->player.ray.camera_x;
		game->player.ray.raydiry = game->player.diry
			+ game->player.planey * game->player.ray.camera_x;
		game->player.ray.mapx = (int)game->player.posx;
		game->player.ray.mapy = (int)game->player.posy;
		game->player.ray.deltadistx = fabs(1 / game->player.ray.raydirx);
		game->player.ray.deltadisty = fabs(1 / game->player.ray.raydiry);
		if (game->player.ray.raydirx < 0)
		{
			game->player.ray.stepx = -1;
			game->player.ray.sidedistx = (game->player.posx
				- game->player.ray.mapx) * game->player.ray.deltadistx;
		}
		else
		{
			game->player.ray.stepx = 1;
			game->player.ray.sidedistx = (game->player.ray.mapx + 1.0
				- game->player.posx) * game->player.ray.deltadistx;
		}
		if (game->player.ray.raydiry < 0)
		{
			game->player.ray.stepy = -1;
			game->player.ray.sidedisty = (game->player.posy
				- game->player.ray.mapy) * game->player.ray.deltadisty;
		}
		else
		{
			game->player.ray.stepy = 1;
			game->player.ray.sidedisty = (game->player.ray.mapy + 1.0
				- game->player.posy) * game->player.ray.deltadisty;
		}
		game->player.ray.hit = 0;
		while (game->player.ray.hit == 0)
		{
			if (game->player.ray.sidedistx < game->player.ray.sidedisty)
			{
				game->player.ray.sidedistx += game->player.ray.deltadistx;
				game->player.ray.mapx += game->player.ray.stepx;
				game->player.ray.side = 0;
			}
			else
			{
				game->player.ray.sidedisty += game->player.ray.deltadisty;
				game->player.ray.mapy += game->player.ray.stepy;
				game->player.ray.side = 1;
			}
			if (game->final_map[game->player.ray.mapy][game->player.ray.mapx] == '1')
				game->player.ray.hit = 1;
		}
		if (game->player.ray.side == 0)
			game->player.ray.perpwalldist = (game->player.ray.mapx - game->player.posx
				+ (1 - game->player.ray.stepx) / 2) / game->player.ray.raydirx;
		else
			game->player.ray.perpwalldist = (game->player.ray.mapy - game->player.posy
				+ (1 - game->player.ray.stepy) / 2) / game->player.ray.raydiry;
		game->player.ray.lineheight = (int)(HEIGHT / game->player.ray.perpwalldist);
		game->player.ray.drawstart = -game->player.ray.lineheight / 2 + HEIGHT / 2;
		if (game->player.ray.drawstart < 0)
			game->player.ray.drawstart = 0;
		game->player.ray.drawend = game->player.ray.lineheight / 2 + HEIGHT / 2;
		if (game->player.ray.drawend >= HEIGHT)
			game->player.ray.drawend = HEIGHT - 1;
		draw_vertical_line(game, x,
			game->player.ray.drawstart, game->player.ray.drawend,
			(game->player.ray.side == 1) ? 0xFF0000 : 0x00FF00);
	}
}
