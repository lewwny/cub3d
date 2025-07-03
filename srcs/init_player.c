/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:49:34 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/03 10:01:52 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_player_pos(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->final_map[i])
	{
		j = 0;
		while (game->final_map[i][j])
		{
			if (game->final_map[i][j] == 'N' || game->final_map[i][j] == 'S' ||
				game->final_map[i][j] == 'E' || game->final_map[i][j] == 'W')
			{
				game->player.posx = j + 0.5;
				game->player.posy = i + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
}

static void	init_player_direction(t_game *game)
{
	if (game->final_map[(int)game->player.posy][(int)game->player.posx]
		== 'W')
	{
		game->player.dirx = -1;
		game->player.diry = 0;
	}
	else if (game->final_map[(int)game->player.posy][(int)game->player.posx]
		== 'E')
	{
		game->player.dirx = 1;
		game->player.diry = 0;
	}
	else if (game->final_map[(int)game->player.posy][(int)game->player.posx]
		== 'S')
	{
		game->player.dirx = 0;
		game->player.diry = 1;
	}
	else if (game->final_map[(int)game->player.posy][(int)game->player.posx]
		== 'N')
	{
		game->player.dirx = 0;
		game->player.diry = -1;
	}
}

static void	init_player_plane(t_game *game)
{
	if (game->final_map[(int)game->player.posy][(int)game->player.posx] == 'N')
	{
		game->player.planex = 0;
		game->player.planey = 0.66;
	}
	else if (game->final_map[(int)game->player.posy][(int)game->player.posx]
		== 'S')
	{
		game->player.planex = 0;
		game->player.planey = -0.66;
	}
	else if (game->final_map[(int)game->player.posy][(int)game->player.posx]
		== 'E')
	{
		game->player.planex = 0.66;
		game->player.planey = 0;
	}
	else if (game->final_map[(int)game->player.posy][(int)game->player.posx]
		== 'W')
	{
		game->player.planex = -0.66;
		game->player.planey = 0;
	}
}

void	init_player(t_game *game)
{
	init_player_pos(game);
	init_player_direction(game);
	init_player_plane(game);
}
