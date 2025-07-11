/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:29:30 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/11 19:01:59 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_lifebar(t_game *game)
{
	int	tmp_width;
	int	tmp_height;
	int	i;

	i = 0;
	game->lifebar[0] = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/lifebar1.xpm", &tmp_width, &tmp_height);
	game->lifebar[1] = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/lifebar2.xpm", &tmp_width, &tmp_height);
	game->lifebar[2] = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/lifebar3.xpm", &tmp_width, &tmp_height);
	game->lifebar[3] = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/lifebar4.xpm", &tmp_width, &tmp_height);
	game->lifebar[4] = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/lifebar5.xpm", &tmp_width, &tmp_height);
	while (i < 5)
	{
		if (!game->lifebar[i] || tmp_width != 400 || tmp_height != 91)
			destroy_game_failure(game, "Error: Failed to load lifebar image.");
		game->buf_lifebar[i] = (int *)mlx_get_data_addr(game->lifebar[i],
				&game->width, &game->line_len, &game->bpp);
		i++;
	}
}

void	load_crosshair(t_game *game)
{
	int	tmp_width;
	int	tmp_height;

	game->crosshair1 = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/crosshair1.xpm", &tmp_width, &tmp_height);
	if (!game->crosshair1 || tmp_width != 13 || tmp_height != 13)
		destroy_game_failure(game, "Error: Failed to load crosshair1 image.");
	game->bufcrosshair1 = (int *)mlx_get_data_addr(game->crosshair1,
			&game->width, &game->line_len, &game->bpp);
	game->crosshair2 = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/crosshair2.xpm", &tmp_width, &tmp_height);
	if (!game->crosshair2 || tmp_width != 13 || tmp_height != 13)
		destroy_game_failure(game, "Error: Failed to load crosshair2 image.");
	game->bufcrosshair2 = (int *)mlx_get_data_addr(game->crosshair2,
			&game->width, &game->line_len, &game->bpp);
}

static void	load_quitdeath_images(t_game *game)
{
	int	tmp_width;
	int	tmp_height;

	game->quitdeath1 = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/quitdeath1.xpm", &tmp_width, &tmp_height);
	if (!game->quitdeath1 || tmp_width != 300 || tmp_height != 300)
		destroy_game_failure(game, "Error: Failed to load quitdeath1 image.");
	game->bufquitdeath1 = (int *)mlx_get_data_addr(game->quitdeath1,
			&game->width, &game->line_len, &game->bpp);
	game->quitdeath2 = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/quitdeath2.xpm", &tmp_width, &tmp_height);
	if (!game->quitdeath2 || tmp_width != 300 || tmp_height != 300)
		destroy_game_failure(game, "Error: Failed to load quitdeath2 image.");
	game->bufquitdeath2 = (int *)mlx_get_data_addr(game->quitdeath2,
			&game->width, &game->line_len, &game->bpp);
}

static void	load_respawn_images(t_game *game)
{
	int	tmp_width;
	int	tmp_height;

	game->respawn1 = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/respawn1.xpm", &tmp_width, &tmp_height);
	if (!game->respawn1 || tmp_width != 300 || tmp_height != 300)
		destroy_game_failure(game, "Error: Failed to load respawn1 image.");
	game->bufrespawn1 = (int *)mlx_get_data_addr(game->respawn1,
			&game->width, &game->line_len, &game->bpp);
	game->respawn2 = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/respawn2.xpm", &tmp_width, &tmp_height);
	if (!game->respawn2 || tmp_width != 300 || tmp_height != 300)
		destroy_game_failure(game, "Error: Failed to load respawn2 image.");
	game->bufrespawn2 = (int *)mlx_get_data_addr(game->respawn2,
			&game->width, &game->line_len, &game->bpp);
}

void	load_death_menu(t_game *game)
{
	load_respawn_images(game);
	load_quitdeath_images(game);
}
