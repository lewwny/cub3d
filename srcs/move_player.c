/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:04:31 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/07 18:31:00 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	calculate_target(t_game *game, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = game->player.posx + dx;
	new_y = game->player.posy + dy;
	if (game->final_map[(int)(game->player.posy + dy)]
		[(int)(game->player.posx)]== '1')
		new_y = game->player.posy;
	if (game->final_map[(int)(game->player.posy)]
		[(int)(game->player.posx + dx)] == '1')
		new_x = game->player.posx;
	game->move_anim.end_x = new_x;
	game->move_anim.end_y = new_y;
}

static void	update_anim_target(t_game *game, double dx, double dy)
{
	double	base_x;
	double	base_y;
	double	new_target_x;
	double	new_target_y;

	base_x = game->move_anim.end_x;
	base_y = game->move_anim.end_y;
	new_target_x = base_x + dx;
	new_target_y = base_y + dy;
	if (game->final_map[(int)(base_y + dy)][(int)base_x] == '1')
		new_target_y = base_y;
	if (game->final_map[(int)base_y][(int)(base_x + dx)] == '1')
		new_target_x = base_x;
	game->move_anim.end_x = new_target_x;
	game->move_anim.end_y = new_target_y;
	if (game->move_anim.total_frames - game->move_anim.frame < 5)
		game->move_anim.total_frames += 4;
}

void	schedule_move(t_game *game, double dx, double dy)
{
	if (game->move_anim.type == ANIM_MOVE)
	{
		update_anim_target(game, dx, dy);
		return;
	}
	calculate_target(game, dx, dy);
	game->move_anim.type = ANIM_MOVE;
	game->move_anim.start_x = game->player.posx;
	game->move_anim.start_y = game->player.posy;
	game->move_anim.total_frames = 8;
	game->move_anim.frame = 0;
	game->move_anim.ease_fn = ease_linear;
}

void	move_player(t_game *game, int keycode)
{
	double	speed;

	speed = 0.018;
	if (keycode == KEY_W)
		schedule_move(game, game->player.dirx * speed,
			game->player.diry * speed);
	else if (keycode == KEY_S)
		schedule_move(game, -game->player.dirx * speed,
			-game->player.diry * speed);
	else if (keycode == KEY_A)
		schedule_move(game, game->player.diry * speed,
			-game->player.dirx * speed);
	else if (keycode == KEY_D)
		schedule_move(game, -game->player.diry * speed,
			game->player.dirx * speed);
}
