/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failure.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:02:30 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/11 19:03:31 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	destroy_game_images(t_game *game)
{
	if (game->mlx_ptr && game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->menu)
		mlx_destroy_image(game->mlx_ptr, game->menu);
	if (game->menu2)
		mlx_destroy_image(game->mlx_ptr, game->menu2);
	if (game->menu3)
		mlx_destroy_image(game->mlx_ptr, game->menu3);
	if (game->texture.no)
		mlx_destroy_image(game->mlx_ptr, game->texture.no);
	if (game->texture.so)
		mlx_destroy_image(game->mlx_ptr, game->texture.so);
	if (game->texture.we)
		mlx_destroy_image(game->mlx_ptr, game->texture.we);
	if (game->texture.ea)
		mlx_destroy_image(game->mlx_ptr, game->texture.ea);
	if (game->buftmp)
		mlx_destroy_image(game->mlx_ptr, game->buftmp);
	if (game->resume)
		mlx_destroy_image(game->mlx_ptr, game->resume);
	if (game->quit)
		mlx_destroy_image(game->mlx_ptr, game->quit);
	if (game->menuimg.quit2)
		mlx_destroy_image(game->mlx_ptr, game->menuimg.quit2);
}

static void	destroy_game_lifebar_and_wait(t_game *game)
{
	if (game->lifebar[0])
		mlx_destroy_image(game->mlx_ptr, game->lifebar[0]);
	if (game->lifebar[1])
		mlx_destroy_image(game->mlx_ptr, game->lifebar[1]);
	if (game->lifebar[2])
		mlx_destroy_image(game->mlx_ptr, game->lifebar[2]);
	if (game->lifebar[3])
		mlx_destroy_image(game->mlx_ptr, game->lifebar[3]);
	if (game->lifebar[4])
		mlx_destroy_image(game->mlx_ptr, game->lifebar[4]);
	if (game->wait)
		mlx_destroy_image(game->mlx_ptr, game->wait);
}

static void	destroy_game_other_images(t_game *game)
{
	if (game->gun)
		mlx_destroy_image(game->mlx_ptr, game->gun);
	if (game->menuimg.resume2)
		mlx_destroy_image(game->mlx_ptr, game->menuimg.resume2);
	if (game->gun2)
		mlx_destroy_image(game->mlx_ptr, game->gun2);
	if (game->crosshair1)
		mlx_destroy_image(game->mlx_ptr, game->crosshair1);
	if (game->crosshair2)
		mlx_destroy_image(game->mlx_ptr, game->crosshair2);
	if (game->respawn1)
		mlx_destroy_image(game->mlx_ptr, game->respawn1);
	if (game->respawn2)
		mlx_destroy_image(game->mlx_ptr, game->respawn2);
	if (game->quitdeath1)
		mlx_destroy_image(game->mlx_ptr, game->quitdeath1);
	if (game->quitdeath2)
		mlx_destroy_image(game->mlx_ptr, game->quitdeath2);
}

void	destroy_game_failure(t_game *game, const char *message)
{
	destroy_game_images(game);
	destroy_game_lifebar_and_wait(game);
	destroy_game_other_images(game);
	if (game->tmp)
		free_split(game->tmp);
	if (game->sock > 2)
	{
		close(game->sock);
		game->sock = 0;
	}
	free_linux(game);
	if (game->mlx_ptr)
		free(game->mlx_ptr);
	ft_dprintf(2, "Error\n%s\n", message);
	free_all(&game->garbage);
	join_thread(game);
	close_server(game);
	exit(EXIT_FAILURE);
}
