/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fc_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:17:27 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/11 17:16:10 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_valid_cell(t_game *game, int cell_x, int cell_y)
{
	return !(cell_x < 0 || cell_y < 0 || cell_x >= game->width
		|| cell_y >= game->height);
}

static int	is_valid_floor(int is_floor)
{
	return (is_floor >= 0 && is_floor < 4);
}

static void	calc_frac(t_game *game, int cell_x, int cell_y)
{
	double	tile_scale;
	
	game->rot.rotate = (cell_x + cell_y) % 2;
	tile_scale = 4.0;
	game->rot.frac_x = fmod(game->player.ray.floor.floor_x * tile_scale, 1.0);
	game->rot.frac_y = fmod(game->player.ray.floor.floor_y * tile_scale, 1.0);
	if (game->rot.frac_x < 0)
		game->rot.frac_x += 1.0;
	if (game->rot.frac_y < 0)
		game->rot.frac_y += 1.0;
}

static void	get_tex_coords(t_game *game, int *tx, int *ty)
{
	if (game->rot.rotate)
	{
		*tx = (int)(TEX_WIDTH * (1.0 - game->rot.frac_y)) & (TEX_WIDTH - 1);
		*ty = (int)(TEX_HEIGHT * game->rot.frac_x) & (TEX_HEIGHT - 1);
	}
	else
	{
		*tx = (int)(TEX_WIDTH * game->rot.frac_x) & (TEX_WIDTH - 1);
		*ty = (int)(TEX_HEIGHT * game->rot.frac_y) & (TEX_HEIGHT - 1);
	}
	if (*tx < 0)
		*tx = 0;
	else if (*tx >= TEX_WIDTH)
		*tx = TEX_WIDTH - 1;
	if (*ty < 0)
		*ty = 0;
	else if (*ty >= TEX_HEIGHT)
		*ty = TEX_HEIGHT - 1;
}

unsigned int	get_fc_text_color(t_game *game, int is_floor)
{
	int			cell_x;
	int			cell_y;
	int			tx;
	int			ty;
	t_tex_data	*tex;

	cell_x = (int)game->player.ray.floor.floor_x;
	cell_y = (int)game->player.ray.floor.floor_y;
	if (!is_valid_cell(game, cell_x, cell_y))
		return (0x000000);
	if (!is_valid_floor(is_floor))
		return (0x000000);
	calc_frac(game, cell_x, cell_y);
	get_tex_coords(game, &tx, &ty);
	tex = &game->texture.tex_ptr[is_floor];
	if (!(tex && tex->data && tx >= 0 && ty >= 0
			&& tx < tex->width && ty < tex->height))
		return (0x000000);
	return (tex->data[ty * tex->width + tx]);
}
