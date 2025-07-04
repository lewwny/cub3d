/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:54:43 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/04 21:03:25 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	wall_height(t_game *game)
{
	t_ray	*ray;

	ray = &game->player.ray;
	ray->wall.height = (int)(HEIGHT / ray->distance);
	ray->wall.start = -ray->wall.height / 2 + HEIGHT / 2 + game->player.pitch;
	if (ray->wall.start < 0)
		ray->wall.start = 0;
	ray->wall.end = ray->wall.height / 2 + HEIGHT / 2 + game->player.pitch;
	if (ray->wall.end >= HEIGHT)
		ray->wall.end = HEIGHT;
}

void	cast_ray(t_game *game, double raydirx, double raydiry, int column)
{
	(void)column;
	game->player.ray.rayx = game->player.posx;
	game->player.ray.rayy = game->player.posy;
	game->player.ray.stepsize = 0.005;
	game->player.ray.distance = 0.0;
	while (1)
	{
		game->player.ray.rayx += raydirx * game->player.ray.stepsize;
		game->player.ray.rayy += raydiry * game->player.ray.stepsize;
		game->player.ray.distance += game->player.ray.stepsize;
		game->player.ray.mapx = (int)game->player.ray.rayx;
		game->player.ray.mapy = (int)game->player.ray.rayy;
		if (game->player.ray.mapx < 0 || game->player.ray.mapx >= game->width
			|| game->player.ray.mapy < 0
			|| game->player.ray.mapy >= game->height)
			break ;
		if (game->final_map[game->player.ray.mapy][game->player.ray.mapx]
				== '1')
			break ;
	}
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
			game->buf[y * WIDTH + x] = game->color.ceiling.r << 16
				| game->color.ceiling.g << 8 | game->color.ceiling.b;
		else if (y >= ray->wall.start && y < ray->wall.end)
			game->buf[y * WIDTH + x] = 0x654321;
		else
			game->buf[y * WIDTH + x] = game->color.floor.r << 16
				| game->color.floor.g << 8 | game->color.floor.b;
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
		cast_ray(game, raydirx, raydiry, x);
		game->player.ray.distance *= (raydirx * game->player.dirx)
			+ (raydiry * game->player.diry);
		wall_height(game);
		draw_wall(game, x);
		x++;
	}
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->buftmp, 0, 0);
}
