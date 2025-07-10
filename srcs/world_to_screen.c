/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:23:36 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/10 17:23:41 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static double	calculate_relative_angle(t_game *game, double world_x,
		double world_y)
{
	double	dx;
	double	dy;
	double	angle_to_sprite;
	double	player_angle;

	dx = world_x - game->player.posx;
	dy = world_y - game->player.posy;
	angle_to_sprite = atan2(dy, dx);
	player_angle = atan2(game->player.diry, game->player.dirx);
	return (normalize_angle(angle_to_sprite - player_angle));
}

static bool	is_sprite_in_range(t_game *game, double world_x, double world_y)
{
	double	dx;
	double	dy;
	double	distance;

	dx = world_x - game->player.posx;
	dy = world_y - game->player.posy;
	distance = sqrt(dx * dx + dy * dy);
	return (distance >= 0.2 && distance <= 20.0);
}

static void	set_screen_position(t_game *game, double relative_angle,
		int *screen_x, int *screen_y)
{
	*screen_x = (int)(WIDTH / 2 + relative_angle / (game->player.fov / 2.0)
			* WIDTH / 2);
	*screen_y = HEIGHT / 2 + game->player.pitch;
}

bool	world_to_screen_simple(t_game *game, double world_x, double world_y,
		int *screen_x)
{
	double	relative_angle;
	int		screen_y;

	if (!is_sprite_in_range(game, world_x, world_y))
		return (false);
	relative_angle = calculate_relative_angle(game, world_x, world_y);
	if (!is_in_fov(relative_angle))
		return (false);
	set_screen_position(game, relative_angle, screen_x, &screen_y);
	return (*screen_x >= 0 && *screen_x < WIDTH);
}
