#include "../includes/cub3d.h"

static double	calc_row_dist(int y, double pitch, int is_floor)
{
	double denominator;
	if (is_floor)
		denominator = y - (HEIGHT / 2.0 + pitch);
	else
		denominator = (HEIGHT / 2.0 + pitch) - y;
	if (fabs(denominator) < 0.001)
		return -1.0;
	return HEIGHT / (2.0 * denominator);
}

static void	update_floor_coords(t_game *game, double row_dist, double raydirx, double raydiry)
{
	game->player.ray.floor.floor_x = game->player.posx + row_dist * raydirx;
	game->player.ray.floor.floor_y = game->player.posy + row_dist * raydiry;
}

static unsigned int	get_fc_color(t_game *game, double row_dist, int is_floor, double raydirx, double raydiry)
{
	unsigned int	color;
	int				tex_index;

	update_floor_coords(game, row_dist, raydirx, raydiry);
	if (is_floor)
		tex_index = 1;
	else
		tex_index = 2;
	color = get_fc_text_color(game, tex_index);
	return (apply_shading(color, row_dist));
}

static void	draw_fc_row(t_game *game, int x, int start, int end, int is_floor, double raydirx, double raydiry)
{
	int		y;
	double	row_dist;

	if (start < 0)
		y = 0;
	else
		y = start;
	while (y < end && y < HEIGHT)
	{
		row_dist = calc_row_dist(y, game->player.pitch, is_floor);
		if (row_dist < 0 || row_dist > MAX_DIST)
		{
			y++;
			continue;
		}
		game->buf[y * WIDTH + x] = get_fc_color(game, row_dist, is_floor, raydirx, raydiry);
		y++;
	}
}

void	draw_floor_ceil_col(t_game *game, int x, double raydirx, double raydiry)
{
	int	wall_start;
	int	wall_end;

	if (game->player.ray.wall.start < 0)
		wall_start = 0;
	else
		wall_start = game->player.ray.wall.start;
	if (game->player.ray.wall.end >= HEIGHT)
		wall_end = HEIGHT - 1;
	else
		wall_end = game->player.ray.wall.end;
	if (x < 0 || x >= WIDTH)
		return;
	draw_fc_row(game, x, 0, wall_start, 0, raydirx, raydiry);
	draw_fc_row(game, x, wall_end, HEIGHT, 1, raydirx, raydiry);
}
