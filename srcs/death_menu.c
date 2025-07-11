/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:42:00 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/11 19:06:13 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_buttons(t_game *game)
{
	if (!game || !game->buf)
		return ;
	draw_button(game, 490, 110, game->bufrespawn1);
	draw_button(game, 490, 310, game->bufquitdeath1);
}

void	red_filter(t_game *game)
{
	int	i;

	if (!game || !game->buf)
		return ;
	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		game->buf[i] = (game->buf[i] & 0x00FFFF) | 0xFF0000;
		i++;
	}
	draw_buttons(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->buftmp, 0, 0);
}

void	death_menu(t_game *game)
{
	red_filter(game);
	mouse_show(game);
}

static void	update_death_menu(t_game *game, int new_menu_mode)
{
	if (new_menu_mode != game->menu_mode)
	{
		raycasting(game);
		red_filter(game);
		game->menu_mode = new_menu_mode;
		if (game->menu_mode == 11)
		{
			draw_button(game, 490, 110, game->bufrespawn2);
			mlx_put_image_to_window(game->mlx_ptr,
				game->win_ptr, game->buftmp, 0, 0);
		}
		else if (game->menu_mode == 12)
		{
			draw_button(game, 490, 310, game->bufquitdeath2);
			mlx_put_image_to_window(game->mlx_ptr,
				game->win_ptr, game->buftmp, 0, 0);
		}
		else if (game->menu_mode == 10)
		{
			draw_buttons(game);
			mlx_put_image_to_window(game->mlx_ptr,
				game->win_ptr, game->buftmp, 0, 0);
		}
	}
}

int	handle_death_pause_menu_mouse_move(int x, int y, t_game *game)
{
	int	new_menu_mode;

	new_menu_mode = 0;
	if (game->menu_mode >= 10 && game->menu_mode <= 12)
	{
		if (x >= 510 && x <= 750 && y >= 210 && y <= 310)
			new_menu_mode = 11;
		else if (x >= 510 && x <= 750 && y >= 410 && y <= 510)
			new_menu_mode = 12;
		else
			new_menu_mode = 10;
		update_death_menu(game, new_menu_mode);
		return (0);
	}
	if (game->menu_mode >= 5 && game->menu_mode <= 9)
	{
		if (x >= 540 && x <= 750 && y >= 264 && y <= 334)
			new_menu_mode = 6;
		else if (x >= 540 && x <= 750 && y >= 385 && y <= 455)
			new_menu_mode = 7;
		else
			new_menu_mode = 5;
		return (update_pause_menu(game, new_menu_mode), 0);
	}
	return (-1);
}
