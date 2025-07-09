#include "../includes/cub3d.h"

static unsigned int	get_fc_text_color(t_game *game, int is_floor)
{
	int			cell_x;
	int			cell_y;
	int			tx;
	int			ty;
	t_tex_data	*tex;

	cell_x = (int)game->player.ray.floor.floor_x;
	cell_y = (int)game->player.ray.floor.floor_y;
	if (cell_x < 0 || cell_y < 0 || cell_x >= game->width || cell_y >= game->height)
		return (0);
	tx = (int)(TEX_WIDTH * (game->player.ray.floor.floor_x - cell_x))
			& (TEX_WIDTH - 1);
	ty = (int)(TEX_HEIGHT * (game->player.ray.floor.floor_y - cell_y))
			& (TEX_HEIGHT - 1);
	tex = &game->texture.tex_ptr[is_floor];
	return (tex->data[ty * tex->width + tx]);
}

void	draw_ceil_col(t_game *game, int x, double raydirx, double raydiry)
{
	int		y;
	double	row_dist;
	t_ray	*ray;

	ray = &game->player.ray;
	y = 0;
	while (y < ray->wall.start)
	{
		row_dist = HEIGHT / (2.0 * ((HEIGHT / 2.0 + game->player.pitch) - y));
		ray->floor.floor_x = game->player.posx + row_dist * raydirx;
		ray->floor.floor_y = game->player.posy + row_dist * raydiry;
		game->buf[y * WIDTH + x] = get_fc_text_color(game, 2);
		y++;
	}
}

void	draw_floor_col(t_game *game, int x, double raydirx, double raydiry)
{
	int		y;
	t_ray	*ray;
	double	row_dist;
	//double	step_x;
	//double	step_y;

	ray = &game->player.ray;
	y = ray->wall.end;
	while (y < HEIGHT)
	{
		row_dist = HEIGHT / (2.0 * (y - (HEIGHT / 2.0 + game->player.pitch)));
		//step_x = row_dist * raydirx / WIDTH;
		//step_y = row_dist * raydiry / WIDTH;
		ray->floor.floor_x = game->player.posx + row_dist * raydirx;
		ray->floor.floor_y = game->player.posy + row_dist * raydiry;
		game->buf[y * WIDTH + x] = get_fc_text_color(game, 1);
		y++;
	}
}
