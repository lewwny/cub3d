/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:56:34 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/07 15:50:09 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_player_by_mouse(t_game *game, int delta_x)
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
		// raycasting(game);
	}
}

// int	on_mouse_move(int x, int y, t_game *game)
// {
// 	int	new_menu_mode;

// 	new_menu_mode = 0;
// 	if (game->menu_mode == 4)
// 	{
// 		mouse_control(game, x, y);
// 		return (0);
// 	}
// 	if (x >= 404 && x <= 957 && y >= 144 && y <= 324)
// 		new_menu_mode = 1;
// 	else if (x >= 404 && x <= 957 && y >= 486 && y <= 657)
// 		new_menu_mode = 2;
// 	if (new_menu_mode != game->menu_mode)
// 		update_menu_mode(game, new_menu_mode);
// 	game->menu_mode = new_menu_mode;
// 	return (0);
// }

// int	on_mouse_click(int button, int x, int y, t_game *game)
// {
// 	(void)x;
// 	(void)y;
// 	if (button == 1 && game->menu_mode == 2)
// 		destroy_game(game);
// 	if (button == 1 && game->menu_mode == 1)
// 	{
// 		mlx_clear_window(game->mlx_ptr, game->win_ptr);
// 		game->menu_mode = 4;
// 		raycasting(game);
// 		mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
// 	}
// 	return (0);
// }

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
	// raycasting(game);
}

int	key_hook(int keycode, t_game *game)
{
	if ((keycode == KEY_W || keycode == KEY_A || keycode == KEY_S
			|| keycode == KEY_D) && game->menu_mode == 4)
		move_player(game, keycode);
	if (keycode == KEY_LEFT && game->menu_mode == 4)
		turn_player(game, -1);
	if (keycode == KEY_RIGHT && game->menu_mode == 4)
		turn_player(game, 1);
	return (0);
}
