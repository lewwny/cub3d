/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:50:08 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/07 18:51:02 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	rotate_player_horizontal(t_game *game, int delta_x)
{
	double	rot_speed;
	double	old_dirx;
	double	old_planex;
	double	angle;

	if (delta_x == 0)
		return (0);
	rot_speed = 0.0005;
	angle = delta_x * rot_speed;
	old_dirx = game->player.dirx;
	old_planex = game->player.planex;
	game->player.dirx = game->player.dirx * cos(angle)
		- game->player.diry * sin(angle);
	game->player.diry = old_dirx * sin(angle)
		+ game->player.diry * cos(angle);
	game->player.planex = game->player.planex * cos(angle)
		- game->player.planey * sin(angle);
	game->player.planey = old_planex * sin(angle)
		+ game->player.planey * cos(angle);
	return (1);
}

static int	rotate_player_vertical(t_game *game, int delta_y)
{
	if (delta_y == 0)
		return (0);
	game->player.pitch -= delta_y;
	if (game->player.pitch > 400)
		game->player.pitch = 400;
	else if (game->player.pitch < -400)
		game->player.pitch = -400;
	return (1);
}

int	rotate_player_by_mouse(t_game *game, int delta_x, int delta_y)
{
	int	rotated;

	rotated = 0;
	rotated |= rotate_player_horizontal(game, delta_x);
	rotated |= rotate_player_vertical(game, delta_y);
	return (rotated);
}
