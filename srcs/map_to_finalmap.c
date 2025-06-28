/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_finalmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:15:04 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/28 16:27:59 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_to_finalmap(t_game *game, int i)
{
	int	j;

	j = i;
	while (game->map[i])
		i++;
	game->final_map = _malloc(sizeof(char *) * (i - j + 1), &game->garbage);
	i = 0;
	while (game->map[j])
	{
		game->final_map[i] = ft_strdup(game->map[j]);
		if (!game->final_map[i])
			destroy_game_failure(game,
				"Memory allocation error for final map.");
		i++;
		j++;
	}
	game->final_map[i] = NULL;
}
