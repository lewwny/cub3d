/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:56:34 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/10 17:45:53 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
