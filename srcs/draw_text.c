#include "../includes/cub3d.h"

static int	match_color_tex(t_game *game)
{
	game->player.ray.wall.color = game->texture.text_ptr[game->player.ray.side][game->player.ray.wall.tex_y
		* (64 * 4) + game->player.ray.wall.tex_x];
	return (game->player.ray.wall.color);
}

void	calculate_y_tex(t_game *game)
{	
	game->player.ray.wall.tex_y = (int)game->player.ray.wall.tex_pos & (64 - 1);
}

void	draw_wall_textured(t_game *game, int x, int y)
{
	set_texture(game);
	game->buf[y * game->width / 4 + x] = match_color_tex(game);
	game->player.ray.wall.tex_pos += game->player.ray.wall.step;
}

