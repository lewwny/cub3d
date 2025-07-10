/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/10 17:25:42 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	put_pixel_safe(t_game *game, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		game->buf[y * WIDTH + x] = color;
}

static void	draw_circle_pixel(t_game *game, int x, int y, int dist_sq)
{
	int	radius_half_sq;
	int	radius_80_sq;

	radius_half_sq = 4;
	radius_80_sq = 16;
	if (dist_sq <= radius_half_sq)
		put_pixel_safe(game, x, y, 0xFFFF00);
	else if (dist_sq <= radius_80_sq)
		put_pixel_safe(game, x, y, 0xFF8800);
	else
		put_pixel_safe(game, x, y, 0xFF0000);
}

static void	draw_small_circle(t_game *game, int cx, int cy, int radius)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	dist_sq;

	y = cy - radius;
	while (y <= cy + radius)
	{
		x = cx - radius;
		while (x <= cx + radius)
		{
			dx = x - cx;
			dy = y - cy;
			dist_sq = dx * dx + dy * dy;
			if (dist_sq <= radius * radius)
				draw_circle_pixel(game, x, y, dist_sq);
			x++;
		}
		y++;
	}
}

static int	calculate_sprite_radius(double distance)
{
	int	sprite_radius;

	sprite_radius = (int)(15.0 / distance * 3.0);
	if (sprite_radius < 2)
		sprite_radius = 2;
	if (sprite_radius > 12)
		sprite_radius = 12;
	return (sprite_radius);
}

void	draw_other_player_simple(t_game *game)
{
	int		screen_x;
	int		screen_y;
	double	distance;
	int		sprite_radius;
	double	other_x;

	if (!game->host && !game->join)
		return ;
	other_x = _other()->otherposx;
	if (other_x == 0.0 && _other()->otherposy == 0.0)
		return ;
	if (!world_to_screen_simple(game, other_x, _other()->otherposy,
			&screen_x))
		return ;
	distance = sqrt(pow(other_x - game->player.posx, 2)
			+ pow(_other()->otherposy - game->player.posy, 2));
	sprite_radius = calculate_sprite_radius(distance);
	screen_y = HEIGHT / 2 + game->player.pitch;
	draw_small_circle(game, screen_x, screen_y, sprite_radius);
}
