/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:42:11 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/07 15:51:02 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	darken_image(t_game *game, int intensity)
{
	int	i;
	int	color;
	int	r;
	int	g;
	int	b;

	if (intensity < 1)
		intensity = 1;
	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		color = game->buf[i];
		r = ((color >> 16) & 0xFF) / intensity;
		g = ((color >> 8) & 0xFF) / intensity;
		b = (color & 0xFF) / intensity;
		((int *)(game->buf))[i] = (color & 0xFF000000)
			| (r << 16) | (g << 8) | b;
		i++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->buftmp, 0, 0);
}

void	update_pause_menu(t_game *game, int new_menu_mode)
{
	if (new_menu_mode != game->menu_mode)
	{
		game->menu_mode = new_menu_mode;
		if (game->menu_mode == 6)
			mlx_put_image_to_window(game->mlx_ptr,
				game->win_ptr, game->menuimg.resume2, 540, 264);
		else if (game->menu_mode == 7)
			mlx_put_image_to_window(game->mlx_ptr,
				game->win_ptr, game->menuimg.quit2, 540, 385);
		else if (game->menu_mode == 5)
		{
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->quit, 540, 385);
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->resume, 540, 264);
		}
	}
}

void	pause_menu(t_game *game)
{
	if (game->menu_mode < 4)
		destroy_game(game);
	if (game->menu_mode >= 5)
	{
		game->menu_mode = 4;
		mouse_hide(game);
		// raycasting(game);
		return ;
	}
	else if (game->menu_mode == 4)
	{
		game->menu_mode = 5;
		mouse_show(game);
		darken_image(game, 3);
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->resume, 540, 264);
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->quit, 540, 385);
	}
}

void	quit_game(t_game *game)
{
	destroy_game(game);
}
