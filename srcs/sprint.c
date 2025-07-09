/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 09:46:23 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/09 10:37:20 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	sprint_on(t_game *game)
{
	if (game->menu_mode != 4)
		return ;
	game->player.target_fov = 0.85;
	game->player.move_speed = 0.03;
}

void	sprint_off(t_game *game)
{
	if (game->menu_mode != 4)
		return ;
	game->player.target_fov = 0.66;
	game->player.move_speed = 0.015;
}

void	fov_sprint(t_game *game)
{
	double	fov_speed;

	if (game->menu_mode != 4)
		return ;
	fov_speed = 5;
	if (game->player.fov < game->player.target_fov)
		game->player.fov += game->delta_time * fov_speed;
	else if (game->player.fov > game->player.target_fov)
		game->player.fov -= game->delta_time * fov_speed;
	if (game->player.fov < 0.66)
		game->player.fov = 0.66;
	if (game->player.fov > 0.85)
		game->player.fov = 0.85;
}

void	handle_sprint(t_game *game)
{
	if (game->menu_mode != 4)
		return ;
	if (game->keys.shift && game->keys.w)
		sprint_on(game);
	else if (!game->keys.shift || !game->keys.w)
		sprint_off(game);
}
