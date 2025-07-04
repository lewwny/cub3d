/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:54:43 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/04 13:38:45 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	wall_height(t_game *game)
{
	t_ray	*ray;

	ray = &game->player.ray;
	ray->wall.height = (int)(HEIGHT / ray->distance);
	ray->wall.start = -ray->wall.height / 2 + HEIGHT / 2;
	if (ray->wall.start < 0)
		ray->wall.start = 0;
	ray->wall.end = ray->wall.height / 2 + HEIGHT / 2;
	if (ray->wall.end >= HEIGHT)
		ray->wall.end = HEIGHT - 1;
}

void	cast_ray(t_game *game, double raydirx, double raydiry)
{
	t_ray	*ray;

	ray = &game->player.ray;
	ray->ray_x = game->player.posx;
	ray->ray_y = game->player.posy;
	ray->mapx = (int)ray->ray_x;
	ray->mapy = (int)ray->ray_y;
	init_sides(game, raydirx, raydiry);
	game->player.ray.hit = false;
	perform_dda(game);
}

static void	draw_wall(t_game *game, int x)
{
	t_ray	*ray;
	int		y;

	ray = &game->player.ray;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < ray->wall.start)
			game->buf[y * WIDTH + x] = 0xADD8E6;
		else if (y >= ray->wall.start && y < ray->wall.end)
			color_sides(game, x, y);
		else
			game->buf[y * WIDTH + x] = 0x008000;
		y++;
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
		ray_angle = atan2(game->player.diry, game->player.dirx)
			+ camera_x * (0.66 / 2.0);
		raydirx = cos(ray_angle);
		raydiry = sin(ray_angle);
		cast_ray(game, raydirx, raydiry);
		game->player.ray.distance *= (raydirx * game->player.dirx)
			+ (raydiry * game->player.diry);
		wall_height(game);
		draw_wall(game, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->buftmp, 0, 0);
}
