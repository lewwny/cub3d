/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_finalmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:15:04 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/03 09:35:33 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_to_finalmap(t_game *game, int i)
{
	int	j;

	if (!game || !game->map)
		return ;
	j = i;
	while (game->map[i])
		i++;
	game->final_map = _malloc(sizeof(char *) * (i - j + 1), &game->garbage);
	if (!game->final_map)
		destroy_game_failure(game, "Memory allocation failed for final_map.");
	i = 0;
	while (game->map[j])
	{
		if (!game->map[j])
			break ;
		game->final_map[i] = ft_strdup(game->map[j], &game->garbage);
		if (!game->final_map[i])
			destroy_game_failure(game,
				"Memory allocation failed for map line.");
		i++;
		j++;
	}
	game->final_map[i] = NULL;
}
