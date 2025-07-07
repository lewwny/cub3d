/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:56:34 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/07 18:21:50 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// void	rotate_player_by_mouse(t_game *game, int delta_x)
// {
// 	double	rot_speed;
// 	double	old_dirx;
// 	double	old_planex;
// 	double	angle;

// 	rot_speed = 0.0005;
// 	if (delta_x != 0)
// 	{
// 		angle = delta_x * rot_speed;
// 		old_dirx = game->player.dirx;
// 		old_planex = game->player.planex;
// 		game->player.dirx = game->player.dirx * cos(angle)
// 			- game->player.diry * sin(angle);
// 		game->player.diry = old_dirx * sin(angle)
// 			+ game->player.diry * cos(angle);
// 		game->player.planex = game->player.planex * cos(angle)
// 			- game->player.planey * sin(angle);
// 		game->player.planey = old_planex * sin(angle)
// 			+ game->player.planey * cos(angle);
// 	}
// }

static void	turn_player(t_game *game, int direction)
{
	double	old_dirx;

	if (direction == -1)
	{
		old_dirx = game->player.dirx;
		game->player.dirx = game->player.dirx * cos(-0.1)
			- game->player.diry * sin(-0.1);
		game->player.diry = old_dirx * sin(-0.1)
			+ game->player.diry * cos(-0.1);
	}
	else if (direction == 1)
	{
		old_dirx = game->player.dirx;
		game->player.dirx = game->player.dirx * cos(0.1)
			- game->player.diry * sin(0.1);
		game->player.diry = old_dirx * sin(0.1)
			+ game->player.diry * cos(0.1);
	}
	raycasting(game);
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
