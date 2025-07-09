/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smooth_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:30:00 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/09 16:11:43 by lengarci         ###   ########.fr       */
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
	keys->shift = 0;
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

static void	handle_rotation(t_game *game)
{
	double	old_dirx;
	double	rotation_speed;

	if (game->menu_mode != 4)
		return ;
	rotation_speed = 0.0075;
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
	handle_sprint(game);
	game->delta_time = get_delta_time();
	fov_sprint(game);
	if (game->menu_mode == 4)
		raycasting(game);
	if (game->host || game->join)
	{
		pthread_mutex_lock(&game->server.mutex);
		_other()->posx = game->player.posx;
		_other()->posy = game->player.posy;
		pthread_mutex_unlock(&game->server.mutex);
	}
	return (0);
}
