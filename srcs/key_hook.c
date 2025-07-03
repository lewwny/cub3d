/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:56:34 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/03 10:19:12 by lengarci         ###   ########.fr       */
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

static void	turn_player(t_game *game, int direction)
{
	double	old_dirx;

	if (direction == -1)
	{
		old_dirx = game->player.dirx;
		game->player.dirx = game->player.dirx * cos(-0.1)
			- game->player.diry * sin(-0.1);
		game->player.diry = old_dirx * sin(-0.1)
			+ game->player.diry * cos(-0.1);
	}
	else if (direction == 1)
	{
		old_dirx = game->player.dirx;
		game->player.dirx = game->player.dirx * cos(0.1)
			- game->player.diry * sin(0.1);
		game->player.diry = old_dirx * sin(0.1)
			+ game->player.diry * cos(0.1);
	}
	raycasting(game);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		destroy_game(game);
	if ((keycode == KEY_W || keycode == KEY_A || keycode == KEY_S
			|| keycode == KEY_D) && game->menu_mode == 4)
		move_player(game, keycode);
	if (keycode == KEY_LEFT && game->menu_mode == 4)
		turn_player(game, -1);
	if (keycode == KEY_RIGHT && game->menu_mode == 4)
		turn_player(game, 1);
	return (0);
}
