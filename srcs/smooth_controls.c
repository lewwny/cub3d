/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smooth_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:30:00 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/03 19:32:51 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_keys(t_keys *keys)
{
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
	keys->esc = 0;
}

static void	handle_movement(t_game *game)
{
	if (game->menu_mode != 4)
		return ;
	if (game->keys.w)
		move_player(game, KEY_W);
	if (game->keys.s)
		move_player(game, KEY_S);
	if (game->keys.a)
		move_player(game, KEY_A);
	if (game->keys.d)
		move_player(game, KEY_D);
}

static void	handle_rotation(t_game *game)
{
	double	old_dirx;
	double	rotation_speed;

	if (game->menu_mode != 4)
		return ;
	rotation_speed = 0.05;
	if (game->keys.left)
	{
		old_dirx = game->player.dirx;
		game->player.dirx = game->player.dirx * cos(-rotation_speed)
			- game->player.diry * sin(-rotation_speed);
		game->player.diry = old_dirx * sin(-rotation_speed)
			+ game->player.diry * cos(-rotation_speed);
	}
	if (game->keys.right)
	{
		old_dirx = game->player.dirx;
		game->player.dirx = game->player.dirx * cos(rotation_speed)
			- game->player.diry * sin(rotation_speed);
		game->player.diry = old_dirx * sin(rotation_speed)
			+ game->player.diry * cos(rotation_speed);
	}
}

int	game_loop(t_game *game)
{
	if (game->keys.esc)
		destroy_game(game);
	handle_movement(game);
	handle_rotation(game);
	if (game->menu_mode == 4)
		raycasting(game);
	return (0);
}
