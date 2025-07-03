/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:36:01 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/03 09:13:52 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	parse_texture_line(char **line, t_parse *parse, t_game *game)
{
	if (ft_strcmp(line[0], "NO") == 0 && line[1] && !line[2])
	{
		no_parse(line[1], parse, game);
		return (1);
	}
	else if (ft_strcmp(line[0], "SO") == 0 && line[1] && !line[2])
	{
		so_parse(line[1], parse, game);
		return (1);
	}
	else if (ft_strcmp(line[0], "WE") == 0 && line[1] && !line[2])
	{
		we_parse(line[1], parse, game);
		return (1);
	}
	else if (ft_strcmp(line[0], "EA") == 0 && line[1] && !line[2])
	{
		ea_parse(line[1], parse, game);
		return (1);
	}
	return (0);
}

static int	parse_color_line(char **line, t_parse *parse, t_game *game)
{
	if (ft_strcmp(line[0], "F") == 0 && line[1] && !line[2])
	{
		f_parse(line[1], parse, game);
		return (1);
	}
	else if (ft_strcmp(line[0], "C") == 0 && line[1] && !line[2])
	{
		c_parse(line[1], parse, game);
		return (1);
	}
	return (0);
}

static int	parse_line(char **line, t_parse *parse, t_game *game)
{
	if (parse_texture_line(line, parse, game))
		return (1);
	if (parse_color_line(line, parse, game))
		return (1);
	return (0);
}

static void	parse_map_line(t_game *game, t_parse *parse, int *i)
{
	while (game->map[*i])
	{
		if (game->map[*i][0] == '\0')
		{
			(*i)++;
			continue ;
		}
		game->tmp = ft_split(game->map[*i], ' ');
		if (!game->tmp)
			destroy_game_failure(game, "Memory allocation error.");
		if (!parse_line(game->tmp, parse, game))
		{
			free_split(game->tmp);
			game->tmp = NULL;
			break ;
		}
		free_split(game->tmp);
		game->tmp = NULL;
		(*i)++;
	}
	while (game->map[*i] && game->map[*i][0] == '\0')
		(*i)++;
}

void	parse_map(t_game *game, t_parse *parse)
{
	int	i;

	i = 0;
	parse_map_line(game, parse, &i);
	if (!parse->no || !parse->so || !parse->we || !parse->ea
		|| !parse->f || !parse->c)
		destroy_game_failure(game, "Incomplete parsing.");
	map_to_finalmap(game, i);
	parse_finalmap(game);
}
