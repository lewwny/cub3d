/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:55:54 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/10 18:56:08 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cast_ray(t_game *game, double raydirx, double raydiry)
{
	t_ray	*ray;

	ray = &game->player.ray;
	ray->ray_x = game->player.posx;
	ray->ray_y = game->player.posy;
	ray->mapx = (int)ray->ray_x;
	ray->mapy = (int)ray->ray_y;
	init_sides(game, raydirx, raydiry);
	game->player.ray.hit = false;
	perform_dda(game);
}
