/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:32:58 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/07 15:19:14 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	update_menu_mode(t_game *game, int new_menu_mode)
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

void	mouse_control(t_game *game, int x, int y)
{
	static int	previous_x = WIDTH / 2;
	int			delta_x;

	(void)y;
	delta_x = x - previous_x;
	previous_x = x;
	rotate_player_by_mouse(game, delta_x);
	if (x <= 10 || x >= WIDTH - 10)
	{
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIDTH / 2, y);
		previous_x = WIDTH / 2;
	}
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
	return (0);
}
