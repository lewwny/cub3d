/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_finalmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:15:04 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/02 11:53:38 by lengarci         ###   ########.fr       */
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
		game->final_map[i] = ft_strdup(game->map[j], &game->garbage);
		i++;
		j++;
	}
	game->final_map[i] = NULL;
}
