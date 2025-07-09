/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:54:43 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/09 15:28:38 by lengarci         ###   ########.fr       */
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
			game->buf[y * WIDTH + x] = game->color.ceiling.r << 16
				| game->color.ceiling.g << 8 | game->color.ceiling.b;
		else if (y >= ray->wall.start && y < ray->wall.end)
			draw_wall_textured(game, x, y);
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
			+ camera_x * (game->player.fov / 2.0);
		raydirx = cos(ray_angle);
		raydiry = sin(ray_angle);
		cast_ray(game, raydirx, raydiry);
		game->player.ray.distance *= (raydirx * game->player.dirx)
			+ (raydiry * game->player.diry);
		wall_height(game);
		set_texture(game, raydirx, raydiry);
		draw_wall(game, x);
		x++;
	}
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->buftmp, 0, 0);
}
