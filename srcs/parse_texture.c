/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:00:45 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/02 11:54:15 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	no_parse(char *filename, t_parse *parse, t_game *game)
{
	if (parse->no)
		destroy_game_failure(game, "Duplicate NO token in parsing.");
	if (!filename)
		destroy_game_failure(game, "NO path is NULL in parsing.");
	else
	{
		parse->no = 1;
		parse->no_path = ft_strdup(filename, &game->garbage);
	}
}

void	so_parse(char *filename, t_parse *parse, t_game *game)
{
	if (parse->so)
		destroy_game_failure(game, "Duplicate SO token in parsing.");
	if (!filename)
		destroy_game_failure(game, "SO path is NULL in parsing.");
	else
	{
		parse->so = 1;
		parse->so_path = ft_strdup(filename, &game->garbage);
	}
}

void	we_parse(char *filename, t_parse *parse, t_game *game)
{
	if (parse->we)
		destroy_game_failure(game, "Duplicate WE token in parsing.");
	if (!filename)
		destroy_game_failure(game, "WE path is NULL in parsing.");
	else
	{
		parse->we = 1;
		parse->we_path = ft_strdup(filename, &game->garbage);
	}
}

void	ea_parse(char *filename, t_parse *parse, t_game *game)
{
	if (parse->ea)
		destroy_game_failure(game, "Duplicate EA token in parsing.");
	if (!filename)
		destroy_game_failure(game, "EA path is NULL in parsing.");
	else
	{
		parse->ea = 1;
		parse->ea_path = ft_strdup(filename, &game->garbage);
	}
}
