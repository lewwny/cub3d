/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:22:48 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/07 18:25:18 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_game(t_game *game, int argc, char **argv)
{
	ft_bzero(game, sizeof(t_game));
	ft_bzero(&game->player.ray, sizeof(t_ray));
	init_keys(&game->keys);
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
	game->cam_angle = atan2(game->player.diry, game->player.dirx);
	game->cam_target = atan2(game->player.dirx, -game->player.diry);
	game->move_anim.type = ANIM_NONE;
	game->rot_anim.type = ANIM_NONE;
}

void	destroy_game(t_game *game)
{
	mouse_show(game);
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
	mlx_hook(game.win_ptr, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win_ptr, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win_ptr, 6, 1L << 6, on_mouse_move, &game);
	mlx_hook(game.win_ptr, 4, 1L << 2, on_mouse_click, &game);
	mlx_hook(game.win_ptr, 17, 0, close_game, &game);
	mlx_loop_hook(game.mlx_ptr, game_loop, &game);
	mlx_loop(game.mlx_ptr);
	destroy_game(&game);
}
