/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:56:34 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/26 20:26:52 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	on_mouse_move(int x, int y, t_game *game)
{
	int	new_menu_mode;

	new_menu_mode = 0;
	if (game->menu_mode == 4)
		return (0);
	if (x >= 404 && x <= 957 && y >= 144 && y <= 324)
		new_menu_mode = 1;
	else if (x >= 404 && x <= 957 && y >= 486 && y <= 657)
		new_menu_mode = 2;
	if (new_menu_mode != game->menu_mode)
	{
		game->menu_mode = new_menu_mode;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		if (game->menu_mode == 1)
			mlx_put_image_to_window(game->mlx_ptr,
				game->win_ptr, game->menu2, 0, 0);
		else if (game->menu_mode == 2)
			mlx_put_image_to_window(game->mlx_ptr,
				game->win_ptr, game->menu3, 0, 0);
		else
			mlx_put_image_to_window(game->mlx_ptr,
				game->win_ptr, game->menu, 0, 0);
	}
	game->menu_mode = new_menu_mode;
	return (0);
}

int	on_mouse_click(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1 && game->menu_mode == 2)
		destroy_game(game);
	if (button == 1 && game->menu_mode == 1)
	{
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		game->menu_mode = 4;
	}
	return (0);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		destroy_game(game);
	}
	return (0);
}
