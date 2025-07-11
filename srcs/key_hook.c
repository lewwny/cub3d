/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:56:34 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/09 18:12:36 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	turn_player(t_game *game, int direction)
{
	double	rotation_speed;
	double	angle;
	double	cos_angle;
	double	sin_angle;
	double	old_dirx;
	double	old_planex;

	rotation_speed = 0.015;
	if (direction == -1)
		angle = -rotation_speed;
	else if (direction == 1)
		angle = rotation_speed;
	else
		return;

	// Apply rotation directly using rotation matrix
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	
	// Rotate direction vector
	old_dirx = game->player.dirx;
	game->player.dirx = game->player.dirx * cos_angle - game->player.diry * sin_angle;
	game->player.diry = old_dirx * sin_angle + game->player.diry * cos_angle;
	
	// Rotate camera plane
	old_planex = game->player.planex;
	game->player.planex = game->player.planex * cos_angle - game->player.planey * sin_angle;
	game->player.planey = old_planex * sin_angle + game->player.planey * cos_angle;
}

int	key_hook(int keycode, t_game *game)
{
	if ((keycode == KEY_W || keycode == KEY_A || keycode == KEY_S
			|| keycode == KEY_D) && game->menu_mode == 4)
		move_player(game, keycode);
	if (keycode == KEY_LEFT && game->menu_mode == 4)
		turn_player(game, -1);
	if (keycode == KEY_RIGHT && game->menu_mode == 4)
		turn_player(game, 1);
	return (0);

}
