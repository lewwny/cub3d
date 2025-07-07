/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:00:05 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/07 15:00:39 by macauchy         ###   ########.fr       */
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
	game->player.ray.wall.tex_y = (int)game->player.ray.wall.tex_pos
		& (game->texture.tex_ptr[game->player.ray.wall.side].height - 1);
}

void	draw_wall_textured(t_game *game, int x, int y)
{
	calculate_y_tex(game);
	game->buf[y * WIDTH + x] = match_color_tex(game);
	game->player.ray.wall.tex_pos += game->player.ray.wall.step;
}
