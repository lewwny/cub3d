/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:30:48 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/02 12:16:31 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_img(t_game *game)
{
	int	tmp;

	game->menu = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/main_menu.xpm", &tmp, &tmp);
	if (!game->menu)
	{
		ft_dprintf(2, "Error: Failed to load image \n");
		destroy_game(game);
	}
	game->menu2 = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/main_menu2.xpm", &tmp, &tmp);
	if (!game->menu2)
	{
		ft_dprintf(2, "Error: Failed to load image \n");
		destroy_game(game);
	}
	game->menu3 = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/main_menu3.xpm", &tmp, &tmp);
	if (!game->menu3)
	{
		ft_dprintf(2, "Error: Failed to load image \n");
		destroy_game(game);
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->menu, 0, 0);
	extract_texture(game);
}
