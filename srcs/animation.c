/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:47:12 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/07 18:51:55 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	handle_rotation_animation(t_game *game, double elapsed)
{
	double	current_angle;

	current_angle = game->rot_anim.start_angle + elapsed * (game->rot_anim.end_angle - game->rot_anim.start_angle);
	game->player.dirx = cos(current_angle);
	game->player.diry = sin(current_angle);
	game->player.planex = -sin(current_angle) * 0.66;
	game->player.planey = cos(current_angle) * 0.66;
}

void	apply_final_rotation(t_game *game)
{
	double	final_angle;

	final_angle = game->rot_anim.end_angle;
	game->player.dirx = cos(final_angle);
	game->player.diry = sin(final_angle);
	game->player.planex = -sin(final_angle) * 0.66;
	game->player.planey = cos(final_angle) * 0.66;
}
static void	handle_move_animation(t_game *game)
{
	double	time;
	double	elapsed;

	if (game->move_anim.frame < game->move_anim.total_frames)
	{
		time = (double)game->move_anim.frame / game->move_anim.total_frames;
		if (game->move_anim.ease_fn)
			elapsed = game->move_anim.ease_fn(time);
		else
			elapsed = time;
		game->player.posx = game->move_anim.start_x
			+ elapsed * (game->move_anim.end_x - game->move_anim.start_x);
		game->player.posy = game->move_anim.start_y
			+ elapsed * (game->move_anim.end_y - game->move_anim.start_y);
		game->move_anim.frame++;
	}
	else
	{
		game->move_anim.type = ANIM_NONE;
		game->player.posx = game->move_anim.end_x;
		game->player.posy = game->move_anim.end_y;
	}
}

static void	handle_rot_animation(t_game *game)
{
	double	time;
	double	elapsed;

	if (game->rot_anim.frame < game->rot_anim.total_frames)
	{
		time = (double)game->rot_anim.frame / game->rot_anim.total_frames;
		if (game->rot_anim.ease_fn)
			elapsed = game->rot_anim.ease_fn(time);
		else
			elapsed = time;
		handle_rotation_animation(game, elapsed);
		game->rot_anim.frame++;
	}
	else
	{
		game->rot_anim.type = ANIM_NONE;
		apply_final_rotation(game);
	}
}

void	handle_animation(t_game *game)
{
	if (game->move_anim.type == ANIM_MOVE)
		handle_move_animation(game);
	if (game->rot_anim.type == ANIM_TURN)
		handle_rot_animation(game);
}

void	start_rotation_animation(t_game *game, double angle_delta)
{
	double	current_angle;
	
	current_angle = atan2(game->player.diry, game->player.dirx);
	game->rot_anim.type = ANIM_TURN;
	game->rot_anim.start_angle = current_angle;
	game->rot_anim.end_angle = current_angle + angle_delta;
	game->rot_anim.frame = 0;
	game->rot_anim.total_frames = 4;
	game->rot_anim.ease_fn = ease_linear;
}

void	extend_rotation_animation(t_game *game, double angle_delta)
{
	double	current_angle;
	double	progress;
	
	if (game->rot_anim.type != ANIM_TURN)
	{
		start_rotation_animation(game, angle_delta);
		return;
	}
	
	current_angle = atan2(game->player.diry, game->player.dirx);
	progress = (double)game->rot_anim.frame / game->rot_anim.total_frames;
	
	if (progress > 0.5)
	{
		game->rot_anim.end_angle += angle_delta;
		game->rot_anim.total_frames = game->rot_anim.frame + 4;
	}
	else
	{
		game->rot_anim.start_angle = current_angle;
		game->rot_anim.end_angle = current_angle + angle_delta;
		game->rot_anim.frame = 0;
		game->rot_anim.total_frames = 4;
	}
}

void	schedule_rotation(t_game *game, double angle_delta)
{
	if (game->rot_anim.type == ANIM_TURN)
	{
		game->rot_anim.end_angle += angle_delta;
		if (game->rot_anim.total_frames - game->rot_anim.frame < 2)
			game->rot_anim.total_frames += 3;
		return;
	}
	start_rotation_animation(game, angle_delta);
}
