/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:30:24 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/28 19:44:13 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	parse_char(char **map, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' &&
				map[i][j] != 'N' &&
				map[i][j] != 'S' && map[i][j] != 'E' &&
				map[i][j] != 'W' && map[i][j] != ' ')
				destroy_game_failure(game, "Invalid character in map.");
			j++;
		}
		i++;
	}
}

static void	verif_player(char **map, t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count == 0)
		destroy_game_failure(game, "No player found in the map.");
	else if (player_count > 1)
		destroy_game_failure(game, "Multiple players found in the map.");
}

static void	verif_wall(char **map, t_game *game)
{
	int		i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N'
				|| map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				if ((i == 0 || !map[i - 1] || map[i - 1][j] == '\0'
					|| map[i - 1][j] == ' ') ||
					(i == ft_strarrlen(map) - 1 || !map[i + 1] ||
					map[i + 1][j] == '\0' || map[i + 1][j] == ' ') ||
					(j == 0 || map[i][j - 1] == '\0' || map[i][j - 1] == ' ') ||
					(j == ft_strlen(map[i]) - 1 || map[i][j + 1] == '\0' ||
					map[i][j + 1] == ' '))
					destroy_game_failure(game, "Map is not surrounded by walls.");
			}
			j++;
		}
		i++;
	}
}

void	parse_finalmap(t_game *game)
{
	parse_char(game->final_map, game);
	verif_player(game->final_map, game);
	verif_wall(game->final_map, game);
}
