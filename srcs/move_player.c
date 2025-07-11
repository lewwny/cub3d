/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:04:31 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/11 14:54:16 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	move_player_forward(t_game *game, double move_speed)
{
	if (can_move_to(game, game->player.posx, game->player.posy + game->player.diry * move_speed))
		game->player.posy += game->player.diry * move_speed * 2;
	if (can_move_to(game, game->player.posx + game->player.dirx * move_speed, game->player.posy))
		game->player.posx += game->player.dirx * move_speed * 2;
}

static void	move_player_backward(t_game *game, double move_speed)
{
	if (can_move_to(game, game->player.posx, game->player.posy - game->player.diry * move_speed))
		game->player.posy -= game->player.diry * move_speed * 2;
	if (can_move_to(game, game->player.posx - game->player.dirx * move_speed, game->player.posy))
		game->player.posx -= game->player.dirx * move_speed * 2;
}

static void	move_player_right(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.posx - game->player.diry * move_speed;
	new_y = game->player.posy + game->player.dirx * move_speed;
	if (can_move_to(game, new_x, game->player.posy))
		game->player.posx = new_x;
	if (can_move_to(game, game->player.posx, new_y))
		game->player.posy = new_y;
}

static void	move_player_left(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.posx + game->player.diry * move_speed;
	new_y = game->player.posy - game->player.dirx * move_speed;
	if (can_move_to(game, new_x, game->player.posy))
		game->player.posx = new_x;
	if (can_move_to(game, game->player.posx, new_y))
		game->player.posy = new_y;
}

void	move_player(t_game *game, int keycode)
{
	double	move_speed;

	move_speed = 0.03;
	if (keycode == KEY_W)
		move_player_forward(game, move_speed);
	else if (keycode == KEY_S)
		move_player_backward(game, move_speed);
	else if (keycode == KEY_A)
		move_player_left(game, move_speed);
	else if (keycode == KEY_D)
		move_player_right(game, move_speed);
}
