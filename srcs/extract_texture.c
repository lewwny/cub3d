/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:42:38 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/07 19:05:48 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	extract_no(t_game *game)
{
	if (game->parse.no == 0 || !game->parse.no_path)
		destroy_game_failure(game, "No texture path for NO or invalid path");
	game->texture.no = mlx_xpm_file_to_image(game->mlx_ptr, game->parse.no_path,
			&game->texture.tex_ptr[NORTH].width,
			&game->texture.tex_ptr[NORTH].height);
	if (!game->texture.no)
		destroy_game_failure(game, "Failed to load NO texture");
	game->texture.tex_ptr[NORTH].data = (unsigned int *)mlx_get_data_addr(
			game->texture.no, &game->texture.tex_ptr[NORTH].bpp,
			&game->texture.tex_ptr[NORTH].size_line,
			&game->texture.tex_ptr[NORTH].endian);
}

static void	extract_so(t_game *game)
{
	if (game->parse.so == 0 || !game->parse.so_path)
		destroy_game_failure(game, "No texture path for SO or invalid path");
	game->texture.so = mlx_xpm_file_to_image(game->mlx_ptr, game->parse.so_path,
			&game->texture.tex_ptr[SOUTH].width,
			&game->texture.tex_ptr[SOUTH].height);
	if (!game->texture.so)
		destroy_game_failure(game, "Failed to load SO texture");
	game->texture.tex_ptr[SOUTH].data = (unsigned int *)mlx_get_data_addr(
			game->texture.so, &game->texture.tex_ptr[SOUTH].bpp,
			&game->texture.tex_ptr[SOUTH].size_line,
			&game->texture.tex_ptr[SOUTH].endian);
}

static void	extract_ea(t_game *game)
{
	if (game->parse.ea == 0 || !game->parse.ea_path)
		destroy_game_failure(game, "No texture path for EA or invalid path");
	game->texture.ea = mlx_xpm_file_to_image(game->mlx_ptr, game->parse.ea_path,
			&game->texture.tex_ptr[EAST].width,
			&game->texture.tex_ptr[EAST].height);
	if (!game->texture.ea)
		destroy_game_failure(game, "Failed to load EA texture");
	game->texture.tex_ptr[EAST].data = (unsigned int *)mlx_get_data_addr(
			game->texture.ea, &game->texture.tex_ptr[EAST].bpp,
			&game->texture.tex_ptr[EAST].size_line,
			&game->texture.tex_ptr[EAST].endian);
}

static void	extract_we(t_game *game)
{
	if (game->parse.we == 0 || !game->parse.we_path)
		destroy_game_failure(game, "No texture path for WE or invalid path");
	game->texture.we = mlx_xpm_file_to_image(game->mlx_ptr, game->parse.we_path,
			&game->texture.tex_ptr[WEST].width,
			&game->texture.tex_ptr[WEST].height);
	if (!game->texture.we)
		destroy_game_failure(game, "Failed to load WE texture");
	game->texture.tex_ptr[WEST].data = (unsigned int *)mlx_get_data_addr(
			game->texture.we, &game->texture.tex_ptr[WEST].bpp,
			&game->texture.tex_ptr[WEST].size_line,
			&game->texture.tex_ptr[WEST].endian);
}

void	extract_texture(t_game *game)
{
	extract_no(game);
	extract_so(game);
	extract_ea(game);
	extract_we(game);
	convert_texture(game);
}
