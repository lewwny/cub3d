/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:38:47 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/09 12:26:51 by lengarci         ###   ########.fr       */
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

void	destroy_game_images(t_game *game)
{
	if (game->mlx_ptr && game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->menu)
		mlx_destroy_image(game->mlx_ptr, game->menu);
	if (game->menu2)
		mlx_destroy_image(game->mlx_ptr, game->menu2);
	if (game->menu3)
		mlx_destroy_image(game->mlx_ptr, game->menu3);
	if (game->texture.no)
		mlx_destroy_image(game->mlx_ptr, game->texture.no);
	if (game->texture.so)
		mlx_destroy_image(game->mlx_ptr, game->texture.so);
	if (game->texture.we)
		mlx_destroy_image(game->mlx_ptr, game->texture.we);
	if (game->texture.ea)
		mlx_destroy_image(game->mlx_ptr, game->texture.ea);
	if (game->buftmp)
		mlx_destroy_image(game->mlx_ptr, game->buftmp);
	if (game->resume)
		mlx_destroy_image(game->mlx_ptr, game->resume);
	if (game->quit)
		mlx_destroy_image(game->mlx_ptr, game->quit);
	if (game->menuimg.quit2)
		mlx_destroy_image(game->mlx_ptr, game->menuimg.quit2);
}

void	destroy_game_failure(t_game *game, const char *message)
{
	destroy_game_images(game);
	if (game->menuimg.resume2)
		mlx_destroy_image(game->mlx_ptr, game->menuimg.resume2);
	if (game->tmp)
		free_split(game->tmp);
	if (game->map)
		free_oldmap(game->map, &game->garbage);
	free_linux(game);
	if (game->mlx_ptr)
		free(game->mlx_ptr);
	ft_dprintf(2, "Error\n%s\n", message);
	free_all(&game->garbage);
	close_server(game);
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

void	free_oldmap(char **map, t_gb **garbage)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		_free(map[i], garbage);
		i++;
	}
	_free(map, garbage);
	map = NULL;
}
