/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:00:05 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/07 18:26:07 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	match_color_tex(t_game *game)
{
	game->player.ray.wall.color = game->texture.tex_ptr
	[game->player.ray.wall.side].data
	[game->player.ray.wall.tex_y
		* game->texture.tex_ptr[game->player.ray.wall.side].width
		+ game->player.ray.wall.tex_x];
	return (game->player.ray.wall.color);
}

void	calculate_y_tex(t_game *game)
{
	int	tex_height;

	tex_height = game->texture.tex_ptr[game->player.ray.wall.side].height;
	game->player.ray.wall.tex_y = (int)game->player.ray.wall.tex_pos;
	if (game->player.ray.wall.tex_y < 0)
		game->player.ray.wall.tex_y = 0;
	else if (game->player.ray.wall.tex_y >= tex_height)
		game->player.ray.wall.tex_y = tex_height - 1;
}

void	draw_wall_textured(t_game *game, int x, int y)
{
	calculate_y_tex(game);
	if (game->player.ray.wall.tex_x >= 0
		&& game->player.ray.wall.tex_x
		< game->texture.tex_ptr[game->player.ray.wall.side].width
		&& game->player.ray.wall.tex_y >= 0
		&& game->player.ray.wall.tex_y
		< game->texture.tex_ptr[game->player.ray.wall.side].height)
		game->buf[y * WIDTH + x] = match_color_tex(game);
	else
		game->buf[y * WIDTH + x] = 0x654321;
	game->player.ray.wall.tex_pos += game->player.ray.wall.step;
}
