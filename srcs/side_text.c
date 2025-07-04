/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:25:18 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/04 10:51:27 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_delta_dist(t_ray *ray, double raydirx, double raydiry)
{
	if (raydirx == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / raydirx);
	if (raydiry == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / raydiry);
}

static void	init_side_x(double posX, double rayX, t_ray *ray)
{
	if (rayX < 0) // ray is moving left
	{
		ray->stepSizeX = -1;
		ray->sideDistX = (posX - ray->mapx) * ray->deltaDistX;
	}
	else // ray is moving right
	{
		ray->stepSizeX = 1;
		ray->sideDistX = (ray->mapx + 1.0 - posX) * ray->deltaDistX;
	}
}

static void	init_side_y(double posY, double rayY, t_ray *ray)
{
	if (rayY < 0) // ray is moving up
	{
		ray->stepSizeY = -1;
		ray->sideDistY = (posY - ray->mapy) * ray->deltaDistY;
	}
	else // ray is moving down
	{
		ray->stepSizeY = 1;
		ray->sideDistY = (ray->mapy + 1.0 - posY) * ray->deltaDistY;
	}
}

void	init_sides(t_game *game, double raydirx, double raydiry)
{
	t_ray		*ray;
	t_player	*player;

	ray = &game->player.ray;
	player = &game->player;
	init_delta_dist(ray, raydirx, raydiry);
	init_side_x(player->posx, raydirx, ray);
	init_side_y(player->posy, raydiry, ray);
}

void	perform_dda(t_game *game)
{
	game->player.ray.hit = false;
	while (!game->player.ray.hit)
	{
		if (game->player.ray.sideDistX < game->player.ray.sideDistY)
		{
			game->player.ray.side = NO_SO;
			game->player.ray.mapx += game->player.ray.stepSizeX;
			game->player.ray.distance = game->player.ray.sideDistX;
			game->player.ray.sideDistX += game->player.ray.deltaDistX;
		}
		else
		{
			game->player.ray.side = WE_EA;
			game->player.ray.mapy += game->player.ray.stepSizeY;
			game->player.ray.distance = game->player.ray.sideDistY;
			game->player.ray.sideDistY += game->player.ray.deltaDistY;
		}
		if (game->player.ray.mapx < 0 || game->player.ray.mapx >= game->width
			|| game->player.ray.mapy < 0
			|| game->player.ray.mapy >= game->height)
			game->player.ray.hit = true;
		if (game->final_map[game->player.ray.mapy][game->player.ray.mapx] == '1')
			game->player.ray.hit = true;
	}
	set_sides(game);
}
