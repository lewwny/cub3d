/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:54:43 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/03 10:57:34 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cast_ray(t_game *game, double raydirx, double raydiry, int column)
{
	(void)column;
	game->player.ray.rayx = game->player.posx;
	game->player.ray.rayy = game->player.posy;
	game->player.ray.stepsize = 0.1;
	game->player.ray.distance = 0.0;
	while (1)
	{
		game->player.ray.rayx += raydirx * game->player.ray.stepsize;
		game->player.ray.rayy += raydiry * game->player.ray.stepsize;
		game->player.ray.distance += game->player.ray.stepsize;
		game->player.ray.mapx = (int)game->player.ray.rayx;
		game->player.ray.mapy = (int)game->player.ray.rayy;
		if (game->final_map[game->player.ray.mapy][game->player.ray.mapx]
				== '1')
		{
			printf("Hit a wall at (%d, %d) after distance %.2f\n",
				game->player.ray.mapx, game->player.ray.mapy,
				game->player.ray.distance);
			break ;
		}
	}
}

void	raycasting(t_game *game)
{
	int		x;
	double	camera_x;
	double	raydirx;
	double	raydiry;
	double	ray_angle;

	x = 0;
	while (x < WIDTH)
	{
		camera_x = (2 * x / (double)WIDTH) - 1;
		ray_angle = atan2(game->player.diry,
				game->player.dirx) + camera_x * (0.66 / 2.0);
		raydirx = cos(ray_angle);
		raydiry = sin(ray_angle);
		cast_ray(game, raydirx, raydiry, x);
		x++;
	}
}
