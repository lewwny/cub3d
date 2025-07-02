/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:42:38 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/02 13:41:18 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	extract_no(t_game *game)
{
	int	z;

	if (game->parse.no == 0)
		destroy_game_failure(game, "No texture path for NO");
	game->texture.no = mlx_xpm_file_to_image(game->mlx_ptr, game->parse.no_path,
			&z, &z);
	if (!game->texture.no)
		destroy_game_failure(game, "Failed to load NO texture");
}

static void	extract_so(t_game *game)
{
	int	z;

	if (game->parse.so == 0)
		destroy_game_failure(game, "No texture path for SO");
	game->texture.so = mlx_xpm_file_to_image(game->mlx_ptr, game->parse.so_path,
			&z, &z);
	if (!game->texture.so)
		destroy_game_failure(game, "Failed to load SO texture");
}

static void	extract_ea(t_game *game)
{
	int	z;

	if (game->parse.ea == 0)
		destroy_game_failure(game, "No texture path for EA");
	game->texture.ea = mlx_xpm_file_to_image(game->mlx_ptr, game->parse.ea_path,
			&z, &z);
	if (!game->texture.ea)
		destroy_game_failure(game, "Failed to load EA texture");
}

static void	extract_we(t_game *game)
{
	int	z;

	if (game->parse.we == 0)
		destroy_game_failure(game, "No texture path for WE");
	game->texture.we = mlx_xpm_file_to_image(game->mlx_ptr, game->parse.we_path,
			&z, &z);
	if (!game->texture.we)
		destroy_game_failure(game, "Failed to load WE texture");
}

void	extract_texture(t_game *game)
{
	extract_no(game);
	extract_so(game);
	extract_ea(game);
	extract_we(game);
}
