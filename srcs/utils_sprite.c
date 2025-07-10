/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:25:52 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/10 17:26:03 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_position_valid(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || y < 0)
		return (false);
	map_x = (int)x;
	map_y = (int)y;
	if (map_y >= ft_strarrlen(game->final_map))
		return (false);
	if (map_x >= (int)ft_strlen(game->final_map[map_y]))
		return (false);
	if (game->final_map[map_y][map_x] == '1')
		return (false);
	return (true);
}

double	normalize_angle(double angle)
{
	while (angle > 3.14159265359)
		angle -= 2 * 3.14159265359;
	while (angle < -3.14159265359)
		angle += 2 * 3.14159265359;
	return (angle);
}

bool	is_in_fov(double relative_angle)
{
	if (relative_angle > 3.14159265359 / 2)
		return (false);
	if (relative_angle < -3.14159265359 / 2)
		return (false);
	return (true);
}
