/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:19:19 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/07 17:15:01 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	mouse_control(t_game *game, int x, int y)
{
	static int	previous_x = WIDTH / 2;
	static int	previous_y = HEIGHT / 2;
	int			delta_x;
	int			delta_y;

	if (!game || !game->mlx_ptr || !game->win_ptr)
		return;
	(void)y;
	delta_x = x - previous_x;
	previous_x = x;
	delta_y = y - previous_y;
	previous_y = y;
	rotate_player_by_mouse(game, delta_x, delta_y);
	mouse_move(game, WIDTH / 2, y);
	previous_x = WIDTH / 2;
}

void	update_menu_mode(t_game *game, int new_menu_mode)
{
	if (new_menu_mode != game->menu_mode)
	{
		game->menu_mode = new_menu_mode;
		if (game->menu_mode == 1)
			mlx_put_image_to_window(game->mlx_ptr,
				game->win_ptr, game->menu2, 0, 0);
		else if (game->menu_mode == 2)
			mlx_put_image_to_window(game->mlx_ptr,
				game->win_ptr, game->menu3, 0, 0);
		else if (game->menu_mode == 0)
			mlx_put_image_to_window(game->mlx_ptr,
				game->win_ptr, game->menu, 0, 0);
	}
}

int	on_mouse_move(int x, int y, t_game *game)
{
	int	new_menu_mode;

	if (!game || !game->mlx_ptr || !game->win_ptr)
		return (0);
	new_menu_mode = 0;
	if (game->menu_mode == 4)
	{
		mouse_control(game, x, y);
		return (0);
	}
	if (game->menu_mode >= 5)
	{
		if (x >= 540 && x <= 750 && y >= 264 && y <= 334)
			new_menu_mode = 6;
		else if (x >= 540 && x <= 750 && y >= 385 && y <= 455)
			new_menu_mode = 7;
		else
			new_menu_mode = 5;
		update_pause_menu(game, new_menu_mode);
		return (0);
	}
	if (x >= 404 && x <= 957 && y >= 144 && y <= 324)
		new_menu_mode = 1;
	else if (x >= 404 && x <= 957 && y >= 486 && y <= 657)
		new_menu_mode = 2;
	update_menu_mode(game, new_menu_mode);
	return (0);
}

int	on_mouse_click(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1 && (game->menu_mode == 2 || game->menu_mode == 7))
		quit_game(game);
	if (button == 1 && (game->menu_mode == 1 || game->menu_mode == 6))
	{
		game->menu_mode = 4;
		raycasting(game);
		mouse_hide(game);
	}
	return (0);
}
