/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:38:47 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/01 17:08:11 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_map(char **map)
{
	int	i;

	if (!map)
	{
		ft_dprintf(2, "Error: Map is NULL.\n");
		return ;
	}
	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	destroy_game_failure(t_game *game, const char *message)
{
	if (game->mlx_ptr && game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
		free(game->mlx_ptr);
	if (game->menu)
		mlx_destroy_image(game->mlx_ptr, game->menu);
	if (game->menu2)
		mlx_destroy_image(game->mlx_ptr, game->menu2);
	if (game->menu3)
		mlx_destroy_image(game->mlx_ptr, game->menu3);
	if (game->tmp)
		free_split(game->tmp);
	ft_dprintf(2, "Error\n%s\n", message);
	free_all(&game->garbage);
	exit(EXIT_FAILURE);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
