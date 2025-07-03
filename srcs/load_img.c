/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:30:48 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/03 09:39:04 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_img(t_game *game)
{
	int	tmp;

	game->menu = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/main_menu.xpm", &tmp, &tmp);
	if (!game->menu)
		destroy_game_failure(game, "Error: Failed to load main menu image.");
	game->menu2 = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/main_menu2.xpm", &tmp, &tmp);
	if (!game->menu2)
		destroy_game_failure(game, "Error: Failed to load main menu2 image.");
	game->menu3 = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/main_menu3.xpm", &tmp, &tmp);
	if (!game->menu3)
		destroy_game_failure(game, "Error: Failed to load main menu3 image.");
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->menu, 0, 0);
	extract_texture(game);
}
