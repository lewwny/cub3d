/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:22:48 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/03 09:58:13 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_game(t_game *game, int argc, char **argv)
{
	ft_bzero(game, sizeof(t_game));
	parsing(argc, argv, game);
	init_player(game);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
	{
		ft_dprintf(2, "Error: Failed to initialize MLX.\n");
		exit(EXIT_FAILURE);
	}
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	if (!game->win_ptr)
	{
		ft_dprintf(2, "Error: Failed to create a new window.\n");
		free(game->mlx_ptr);
		exit(EXIT_FAILURE);
	}
	game->width = WIDTH;
	game->height = HEIGHT;
}

void	destroy_game(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_image(game->mlx_ptr, game->menu);
	mlx_destroy_image(game->mlx_ptr, game->menu2);
	mlx_destroy_image(game->mlx_ptr, game->menu3);
	mlx_destroy_image(game->mlx_ptr, game->texture.no);
	mlx_destroy_image(game->mlx_ptr, game->texture.so);
	mlx_destroy_image(game->mlx_ptr, game->texture.we);
	mlx_destroy_image(game->mlx_ptr, game->texture.ea);
	free_linux(game);
	free(game->mlx_ptr);
	free_all(&game->garbage);
	exit(0);
}

static int	close_game(t_game *game)
{
	destroy_game(game);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	init_game(&game, argc, argv);
	load_img(&game);
	raycasting(&game);
	mlx_key_hook(game.win_ptr, key_hook, &game);
	mlx_hook(game.win_ptr, 6, 1L << 6, on_mouse_move, &game);
	mlx_hook(game.win_ptr, 4, 1L << 2, on_mouse_click, &game);
	mlx_hook(game.win_ptr, 17, 0, close_game, &game);
	mlx_loop(game.mlx_ptr);
	destroy_game(&game);
}
