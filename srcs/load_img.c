/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:30:48 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/07 15:20:54 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	load_menu_images(t_game *game)
{
	int	tmp_width;
	int	tmp_height;

	game->menu = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/main_menu.xpm", &tmp_width, &tmp_height);
	if (!game->menu || tmp_width != 1280 || tmp_height != 720)
		destroy_game_failure(game, "Error: Failed to load main menu image.");
	game->menu2 = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/main_menu2.xpm", &tmp_width, &tmp_height);
	if (!game->menu2 || tmp_width != 1280 || tmp_height != 720)
		destroy_game_failure(game, "Error: Failed to load main menu2 image.");
	game->menu3 = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/main_menu3.xpm", &tmp_width, &tmp_height);
	if (!game->menu3 || tmp_width != 1280 || tmp_height != 720)
		destroy_game_failure(game, "Error: Failed to load main menu3 image.");
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->menu, 0, 0);
}

static void	load_buffer_images(t_game *game)
{
	game->buftmp = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	if (!game->buftmp)
		destroy_game_failure(game, "Failed to create new image");
	game->buf = (int *)mlx_get_data_addr(game->buftmp,
			&game->width, &game->line_len, &game->bpp);
}

static void	load_menu_button_images(t_game *game)
{
	int	tmp_width;
	int	tmp_height;

	game->quit = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/quit.xpm", &tmp_width, &tmp_height);
	if (!game->quit || tmp_width != 210 || tmp_height != 70)
		destroy_game_failure(game, "Error: Failed to load quit image.");
	game->resume = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/resume.xpm", &tmp_width, &tmp_height);
	if (!game->resume || tmp_width != 210 || tmp_height != 70)
		destroy_game_failure(game, "Error: Failed to load resume image.");
	game->menuimg.quit2 = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/quit2.xpm", &tmp_width, &tmp_height);
	if (!game->menuimg.quit2 || tmp_width != 210 || tmp_height != 70)
		destroy_game_failure(game, "Error: Failed to load quit2 image.");
	game->menuimg.resume2 = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/resume2.xpm", &tmp_width, &tmp_height);
	if (!game->menuimg.resume2 || tmp_width != 210 || tmp_height != 70)
		destroy_game_failure(game, "Error: Failed to load resume2 image.");
}

void	load_img(t_game *game)
{
	load_menu_images(game);
	extract_texture(game);
	load_buffer_images(game);
	load_menu_button_images(game);
}
