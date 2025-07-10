/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/10 14:38:32 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	has_wall_between_loop(t_game *game, double *cur, double *step,
		double steps)
{
	int		i;
	int		map_y;
	int		map_x;

	i = 0;
	while (i < (int)steps)
	{
		map_x = (int)cur[0];
		map_y = (int)cur[1];
		if (cur[0] < 0 || cur[1] < 0)
			return (true);
		if (map_y >= ft_strarrlen(game->final_map)
			|| map_x >= (int)ft_strlen(game->final_map[map_y]))
			return (true);
		if (game->final_map[map_y][map_x] == '1')
			return (true);
		cur[0] += step[0];
		cur[1] += step[1];
		i++;
	}
	return (false);
}

static bool	has_wall_between(t_game *game, double x1, double y1,
		double x2, double y2)
{
	double	dx;
	double	dy;
	double	steps;
	double	step[2];
	double	cur[2];

	dx = x2 - x1;
	dy = y2 - y1;
	steps = fmax(fabs(dx), fabs(dy)) * 2;
	if (steps == 0)
		return (false);
	step[0] = dx / steps;
	step[1] = dy / steps;
	cur[0] = x1;
	cur[1] = y1;
	return (has_wall_between_loop(game, cur, step, steps));
}

static bool	world_to_screen_simple(t_game *game, double world_x, double world_y,
		int *screen_x, int *screen_y)
{
	double	dx;
	double	dy;
	double	distance;
	double	angle_to_sprite;
	double	player_angle;
	double	relative_angle;
	double	screen_ratio;

	dx = world_x - game->player.posx;
	dy = world_y - game->player.posy;
	distance = sqrt(dx * dx + dy * dy);
	if (distance < SPRITE_MIN_DIST || distance > SPRITE_MAX_DIST)
		return (false);
	angle_to_sprite = atan2(dy, dx);
	player_angle = atan2(game->player.diry, game->player.dirx);
	relative_angle = angle_to_sprite - player_angle;
	while (relative_angle > M_PI)
		relative_angle -= 2 * M_PI;
	while (relative_angle < -M_PI)
		relative_angle += 2 * M_PI;
	if (relative_angle > M_PI / 2 || relative_angle < -M_PI / 2)
		return (false);
	screen_ratio = relative_angle / (game->player.fov / 2.0);
	*screen_x = (int)(WIDTH / 2 + screen_ratio * WIDTH / 2);
	*screen_y = HEIGHT / 2 + game->player.pitch;
	return (*screen_x >= 0 && *screen_x < WIDTH);
}

static void	put_pixel_safe(t_game *game, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		game->buf[y * WIDTH + x] = color;
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
			{
				if (dist_sq <= (radius / 2) * (radius / 2))
					put_pixel_safe(game, x, y, 0xFFFF00);
				else if (dist_sq <= (int)((radius * 0.8) * (radius * 0.8)))
					put_pixel_safe(game, x, y, 0xFF8800);
				else
					put_pixel_safe(game, x, y, 0xFF0000);
			}
			x++;
		}
		y++;
	}
}

void	draw_other_player_simple(t_game *game)
{
	int		screen_x;
	int		screen_y;
	double	distance;
	int		sprite_radius;
	double	other_x;
	double	other_y;

	if (!game->host && !game->join)
		return ;
	other_x = _other()->otherposx;
	other_y = _other()->otherposy;
	if (other_x == 0.0 && other_y == 0.0)
		return ;
	if (has_wall_between(game, game->player.posx, game->player.posy,
			other_x, other_y))
		return ;
	if (!world_to_screen_simple(game, other_x, other_y,
			&screen_x, &screen_y))
		return ;
	distance = sqrt(pow(other_x - game->player.posx, 2)
			+ pow(other_y - game->player.posy, 2));
	sprite_radius = (int)(SPRITE_BASE_RADIUS / distance * SPRITE_RADIUS_SCALE);
	if (sprite_radius < SPRITE_MIN_RADIUS)
		sprite_radius = SPRITE_MIN_RADIUS;
	if (sprite_radius > SPRITE_MAX_RADIUS)
		sprite_radius = SPRITE_MAX_RADIUS;
	draw_small_circle(game, screen_x, screen_y, sprite_radius);
}
