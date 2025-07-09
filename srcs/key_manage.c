/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:32:58 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/09 10:38:02 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	get_delta_time(void)
{
	static struct timeval	last_time = {0};
	struct timeval			current_time;
	double					delta;

	gettimeofday(&current_time, NULL);
	delta = (current_time.tv_sec - last_time.tv_sec)
		+ (current_time.tv_usec - last_time.tv_usec) / 1e6;
	last_time = current_time;
	return (delta);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 1;
	else if (keycode == KEY_A)
		game->keys.a = 1;
	else if (keycode == KEY_S)
		game->keys.s = 1;
	else if (keycode == KEY_D)
		game->keys.d = 1;
	else if (keycode == KEY_LEFT)
		game->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	else if (keycode == KEY_ESC)
		game->keys.esc = 1;
	else if (keycode == KEY_UP)
		game->keys.up = 1;
	else if (keycode == KEY_DOWN)
		game->keys.down = 1;
	else if (keycode == KEY_SHIFT)
		game->keys.shift = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	else if (keycode == KEY_A)
		game->keys.a = 0;
	else if (keycode == KEY_S)
		game->keys.s = 0;
	else if (keycode == KEY_D)
		game->keys.d = 0;
	else if (keycode == KEY_LEFT)
		game->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	else if (keycode == KEY_ESC)
		game->keys.esc = 0;
	else if (keycode == KEY_UP)
		game->keys.up = 0;
	else if (keycode == KEY_DOWN)
		game->keys.down = 0;
	else if (keycode == KEY_SHIFT || !game->keys.w)
		game->keys.shift = 0;
	return (0);
}
