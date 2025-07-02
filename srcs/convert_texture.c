/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:28:10 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/02 17:31:37 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	convert_no(t_game *game)
{
	void	*tmp;
	int		z;

	tmp = mlx_get_data_addr(game->texture.no, &z, &z, &z);
	if (!tmp)
		destroy_game_failure(game, "Failed to convert NO texture");
	game->texture.no_data = (unsigned int *)tmp;
}

static void	convert_so(t_game *game)
{
	void	*tmp;
	int		z;

	tmp = mlx_get_data_addr(game->texture.so, &z, &z, &z);
	if (!tmp)
		destroy_game_failure(game, "Failed to convert SO texture");
	game->texture.so_data = (unsigned int *)tmp;
}

static void	convert_ea(t_game *game)
{
	void	*tmp;
	int		z;

	tmp = mlx_get_data_addr(game->texture.ea, &z, &z, &z);
	if (!tmp)
		destroy_game_failure(game, "Failed to convert EA texture");
	game->texture.ea_data = (unsigned int *)tmp;
}

static void	convert_we(t_game *game)
{
	void	*tmp;
	int		z;

	tmp = mlx_get_data_addr(game->texture.we, &z, &z, &z);
	if (!tmp)
		destroy_game_failure(game, "Failed to convert WE texture");
	game->texture.we_data = (unsigned int *)tmp;
}

void	convert_texture(t_game *game)
{
	convert_no(game);
	convert_so(game);
	convert_ea(game);
	convert_we(game);
}
