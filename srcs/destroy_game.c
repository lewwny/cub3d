/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:32:38 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/11 15:33:20 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	destroy_images(t_game *game)
{
	int	i;

	i = 0;
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_image(game->mlx_ptr, game->menu);
	mlx_destroy_image(game->mlx_ptr, game->menu2);
	mlx_destroy_image(game->mlx_ptr, game->menu3);
	mlx_destroy_image(game->mlx_ptr, game->texture.no);
	mlx_destroy_image(game->mlx_ptr, game->texture.so);
	mlx_destroy_image(game->mlx_ptr, game->texture.we);
	mlx_destroy_image(game->mlx_ptr, game->texture.ea);
	mlx_destroy_image(game->mlx_ptr, game->buftmp);
	mlx_destroy_image(game->mlx_ptr, game->resume);
	mlx_destroy_image(game->mlx_ptr, game->quit);
	mlx_destroy_image(game->mlx_ptr, game->menuimg.quit2);
	mlx_destroy_image(game->mlx_ptr, game->menuimg.resume2);
	mlx_destroy_image(game->mlx_ptr, game->wait);
	mlx_destroy_image(game->mlx_ptr, game->gun);
	mlx_destroy_image(game->mlx_ptr, game->gun2);
	mlx_destroy_image(game->mlx_ptr, game->crosshair1);
	mlx_destroy_image(game->mlx_ptr, game->crosshair2);
	while (i < 5)
		mlx_destroy_image(game->mlx_ptr, game->lifebar[i++]);
}

void	destroy_game(t_game *game)
{
	mouse_show(game);
	destroy_images(game);
	free_linux(game);
	free(game->mlx_ptr);
	free_all(&game->garbage);
	join_thread(game);
	close_server(game);
	exit(0);
}
