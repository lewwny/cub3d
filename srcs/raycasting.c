/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:54:43 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/10 18:57:16 by lengarci         ###   ########.fr       */
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

static void	draw_image_pixels(t_game *game, int *img_data)
{
	int	x;
	int	y;
	int	pixel;

	y = 0;
	while (y < 250)
	{
		x = 0;
		while (x < 395)
		{
			if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			{
				pixel = img_data[y * 395 + x];
				if (pixel != 0x000000)
					game->buf[(y) * WIDTH + (x)] = pixel;
			}
			x++;
		}
		y++;
	}
}

static void	raycasting_column(t_game *game, int x)
{
	double	camera_x;
	double	raydirx;
	double	raydiry;
	double	ray_angle;

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
}

void	raycasting(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		raycasting_column(game, x);
		x++;
	}
	draw_other_player_simple(game);
	pthread_mutex_lock(&game->server.mutex);
	if (game->host && !_other()->connected)
		draw_image_pixels(game, game->wait_buf);
	pthread_mutex_unlock(&game->server.mutex);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->buftmp, 0, 0);
}
