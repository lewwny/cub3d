/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:26:02 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/11 18:19:28 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_gun(t_game *game, int start_x, int start_y, int shoot)
{
	int	x;
	int	y;
	int	pixel;

	y = 0;
	while (y < 525)
	{
		x = 0;
		while (x < 350)
		{
			if (shoot)
				pixel = game->bufgun2[y * 350 + x];
			else
				pixel = game->bufgun[y * 350 + x];
			if (pixel != 0xff00ff)
				game->buf[(start_y + y) * WIDTH + (start_x + x)] = pixel;
			x++;
		}
		y++;
	}
}

void	handle_shoot_animation(t_game *game)
{
	if (game->menu_mode != 4)
		return ;
	if (game->shoot)
	{
		game->shoot_timer += game->delta_time;
		if (game->shoot_timer > 0.1)
		{
			game->shoot = 0;
			game->shoot_timer = 0;
		}
	}
}

void	is_shot(t_game *game)
{
	pthread_mutex_lock(&game->server.mutex);
	_other()->lifebar_state++;
	if (_other()->lifebar_state == 4)
	{
		_other()->lifebar_state = 0;
		game->menu_mode = 10;
		death_menu(game);
	}
	pthread_mutex_unlock(&game->server.mutex);
}
