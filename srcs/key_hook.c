/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:56:34 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/07 18:49:44 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	turn_player(t_game *game, int direction)
{
	double	rotation_speed;

	rotation_speed = 0.015;
	if (direction == -1)
		schedule_rotation(game, -rotation_speed);
	else if (direction == 1)
		schedule_rotation(game, rotation_speed);
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
