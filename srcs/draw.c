/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:28:31 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/11 18:43:07 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_lifebar(t_game *game, int start_x, int start_y)
{
	int	lifebar;
	int	x;
	int	y;
	int	pixel;

	lifebar = _other()->lifebar_state;
	y = 0;
	while (y < 91)
	{
		x = 0;
		while (x < 400)
		{
			pixel = game->buf_lifebar[lifebar][y * 400 + x];
			if (pixel != 0xff00ff)
				game->buf[(start_y + y) * WIDTH + (start_x + x)] = pixel;
			x++;
		}
		y++;
	}
}

void	draw_crosshair(t_game *game, int start_x, int start_y, int shoot)
{
	int	x;
	int	y;
	int	pixel;

	y = 0;
	while (y < 13)
	{
		x = 0;
		while (x < 13)
		{
			if (shoot)
				pixel = game->bufcrosshair2[y * 13 + x];
			else
				pixel = game->bufcrosshair1[y * 13 + x];
			if (pixel != 0xff00ff)
				game->buf[(start_y + y) * WIDTH + (start_x + x)] = pixel;
			x++;
		}
		y++;
	}
}

void	draw_button(t_game *game, int start_x, int start_y, int *buf)
{
	int	x;
	int	y;
	int	pixel;

	y = 0;
	while (y < 300)
	{
		x = 0;
		while (x < 300)
		{
			pixel = buf[y * 300 + x];
			if (pixel != 0xff00ff)
				game->buf[(start_y + y) * WIDTH + (start_x + x)] = pixel;
			x++;
		}
		y++;
	}
}
