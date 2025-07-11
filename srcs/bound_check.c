/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bound_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:22:56 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/11 12:28:16 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_blocked(t_game *game, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (mx < 0 || my < 0 || mx >= game->width || my >= game->height)
		return (1);
	return (game->final_map[my][mx] == '1');
}

int	can_move_to(t_game *game, double x, double y)
{
	if (is_blocked(game, x + COL_BUF, y))
		return (0);
	if (is_blocked(game, x - COL_BUF, y))
		return (0);
	if (is_blocked(game, x, y + COL_BUF))
		return (0);
	if (is_blocked(game, x, y - COL_BUF))
		return (0);
	return (1);
}
