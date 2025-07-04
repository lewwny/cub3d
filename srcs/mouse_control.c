/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:19:19 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/04 17:28:49 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	rotate_player_by_mouse(t_game *game, int delta_x, int delta_y)
{
	double	rot_speed;
	double	old_dirx;
	double	old_planex;
	double	angle;

	rot_speed = 0.0005;
	if (delta_x != 0)
	{
		angle = delta_x * rot_speed;
		old_dirx = game->player.dirx;
		old_planex = game->player.planex;
		game->player.dirx = game->player.dirx * cos(angle)
			- game->player.diry * sin(angle);
		game->player.diry = old_dirx * sin(angle)
			+ game->player.diry * cos(angle);
		game->player.planex = game->player.planex * cos(angle)
			- game->player.planey * sin(angle);
		game->player.planey = old_planex * sin(angle)
			+ game->player.planey * cos(angle);
		return (1);
	}
	(void)delta_y;
	return (0);
}

static void	mouse_control(t_game *game, int x, int y)
{
	static int	previous_x = WIDTH / 2;
	static int	previous_y = HEIGHT / 2;
	int			delta_x;
	int			delta_y;
	int			rotated;

	(void)y;
	delta_x = x - previous_x;
	previous_x = x;
	delta_y = y - previous_y;
	previous_y = y;
	rotated = rotate_player_by_mouse(game, delta_x, delta_y);
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIDTH / 2, y);
	previous_x = WIDTH / 2;
	if (rotated)
		raycasting(game);
}

static void	update_menu_mode(t_game *game, int new_menu_mode)
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
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		game->menu_mode = 4;
		raycasting(game);
		mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
	}
	return (0);
}
