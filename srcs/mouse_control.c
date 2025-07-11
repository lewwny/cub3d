/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:19:19 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/11 19:07:32 by lengarci         ###   ########.fr       */
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
		return ;
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

int	handle_game_menu_mouse_move(int x, int y, t_game *game)
{
	int	ret;
	int	new_menu_mode;

	ret = handle_death_pause_menu_mouse_move(x, y, game);
	if (ret == 0)
		return (0);
	if (game->menu_mode <= 3)
	{
		new_menu_mode = 0;
		if (x >= 404 && x <= 957 && y >= 144 && y <= 324)
			new_menu_mode = 1;
		else if (x >= 404 && x <= 957 && y >= 486 && y <= 657)
			new_menu_mode = 2;
		update_menu_mode(game, new_menu_mode);
	}
	return (0);
}

int	on_mouse_move(int x, int y, t_game *game)
{
	if (!game || !game->mlx_ptr || !game->win_ptr)
		return (0);
	if (game->menu_mode == 4)
	{
		mouse_control(game, x, y);
		return (0);
	}
	return (handle_game_menu_mouse_move(x, y, game));
}

int	on_mouse_click(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1 && game->menu_mode == 4)
	{
		game->shoot = 1;
		is_shot(game);
	}
	if (button == 1 && (game->menu_mode == 2 || game->menu_mode == 7
			|| game->menu_mode == 12))
		quit_game(game);
	if (button == 1 && (game->menu_mode == 1 || game->menu_mode == 6
			|| game->menu_mode == 11))
	{
		if (game->menu_mode == 11)
			respawn_player(game);
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		game->menu_mode = 4;
		raycasting(game);
		mouse_hide(game);
	}
	return (0);
}
