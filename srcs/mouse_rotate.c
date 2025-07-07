/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:50:08 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/07 18:39:24 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	rotate_player_horizontal(t_game *game, int delta_x)
{
	double	rot_speed;
	double	angle;

	if (delta_x == 0)
		return (0);
	rot_speed = ROT_SPEED / 1.5;
	angle = delta_x * rot_speed;
	schedule_rotation(game, angle);
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
