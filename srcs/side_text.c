/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:25:18 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/09 18:25:21 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_delta_dist(t_ray *ray, double raydirx, double raydiry)
{
	if (raydirx == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / raydirx);
	if (raydiry == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / raydiry);
}

static void	init_side_x(double posX, double ray_x, t_ray *ray)
{
	if (ray_x < 0)
	{
		ray->step_size_x = -1;
		ray->side_dist_x = (posX - ray->mapx) * ray->delta_dist_x;
	}
	else
	{
		ray->step_size_x = 1;
		ray->side_dist_x = (ray->mapx + 1.0 - posX) * ray->delta_dist_x;
	}
}

static void	init_side_y(double posY, double ray_y, t_ray *ray)
{
	if (ray_y < 0)
	{
		ray->step_size_y = -1;
		ray->side_dist_y = (posY - ray->mapy) * ray->delta_dist_y;
	}
	else
	{
		ray->step_size_y = 1;
		ray->side_dist_y = (ray->mapy + 1.0 - posY) * ray->delta_dist_y;
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
	while (!game->player.ray.hit)
	{
		if (game->player.ray.side_dist_x < game->player.ray.side_dist_y)
		{
			game->player.ray.side = NO_SO;
			game->player.ray.mapx += game->player.ray.step_size_x;
			game->player.ray.distance = game->player.ray.side_dist_x;
			game->player.ray.side_dist_x += game->player.ray.delta_dist_x;
		}
		else
		{
			game->player.ray.side = WE_EA;
			game->player.ray.mapy += game->player.ray.step_size_y;
			game->player.ray.distance = game->player.ray.side_dist_y;
			game->player.ray.side_dist_y += game->player.ray.delta_dist_y;
		}
		if (game->player.ray.mapx < 0 || game->player.ray.mapx >= game->width
			|| game->player.ray.mapy < 0
			|| game->player.ray.mapy >= game->height)
		{
			game->player.ray.hit = true;
		}
		else if (game->final_map[game->player.ray.mapy][game->player.ray.mapx] == '1')
		{
			game->player.ray.hit = true;
		}
	}
	set_sides(game);
}
