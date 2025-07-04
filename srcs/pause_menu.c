/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:42:11 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/04 15:01:54 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	darken_image(t_game *game)
{
	int	i;
	int	color;
	int	r;
	int	g;
	int	b;

	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		color = game->buf[i];
		r = ((color >> 16) & 0xFF) / 2;
		g = ((color >> 8) & 0xFF) / 2;
		b = (color & 0xFF) / 2;
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
		mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
		raycasting(game);
		return ;
	}
	else if (game->menu_mode == 4)
	{
		game->menu_mode = 5;
		mlx_mouse_show(game->mlx_ptr, game->win_ptr);
		darken_image(game);
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->resume, 540, 264);
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->quit, 540, 385);
	}
}
