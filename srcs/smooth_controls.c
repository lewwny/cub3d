/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smooth_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:30:00 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/11 14:48:44 by macauchy         ###   ########.fr       */
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
	keys->up = 0;
	keys->down = 0;
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

static void	handle_vertical_rotation(t_game *game)
{
	if (game->keys.up && game->player.pitch < 400)
		game->player.pitch += 20;
	if (game->keys.down && game->player.pitch > -400)
		game->player.pitch -= 20;
}

static void	rotate_left(t_game *game, double rotation_speed)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->player.dirx;
	old_planex = game->player.planex;
	game->player.dirx = game->player.dirx * cos(-rotation_speed)
		- game->player.diry * sin(-rotation_speed);
	game->player.diry = old_dirx * sin(-rotation_speed)
		+ game->player.diry * cos(-rotation_speed);
	game->player.planex = game->player.planex * cos(-rotation_speed)
		- game->player.planey * sin(-rotation_speed);
	game->player.planey = old_planex * sin(-rotation_speed)
		+ game->player.planey * cos(-rotation_speed);
}

static void	rotate_right(t_game *game, double rotation_speed)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->player.dirx;
	old_planex = game->player.planex;
	game->player.dirx = game->player.dirx * cos(rotation_speed)
		- game->player.diry * sin(rotation_speed);
	game->player.diry = old_dirx * sin(rotation_speed)
		+ game->player.diry * cos(rotation_speed);
	game->player.planex = game->player.planex * cos(rotation_speed)
		- game->player.planey * sin(rotation_speed);
	game->player.planey = old_planex * sin(rotation_speed)
		+ game->player.planey * cos(rotation_speed);
}

static void	handle_rotation(t_game *game)
{
	double	rotation_speed;

	if (game->menu_mode != 4)
		return ;
	rotation_speed = 0.015;
	if (game->keys.left)
		rotate_left(game, rotation_speed);
	if (game->keys.right)
		rotate_right(game, rotation_speed);
	handle_vertical_rotation(game);
}

int	game_loop(t_game *game)
{
	if (game->keys.esc)
	{
		pause_menu(game);
		game->keys.esc = 0;
	}
	handle_movement(game);
	handle_rotation(game);
	if (game->menu_mode == 4)
		raycasting(game);
	return (0);
}
