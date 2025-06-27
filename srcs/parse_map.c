/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:36:01 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/27 15:51:45 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	parse_line(char **line, t_parse *parse, t_game *game)
{
	if (ft_strcmp(line[0], "NO") == 0 && line[1] && !line[2])
		no_parse(line[1], parse, game);
	else if (ft_strcmp(line[0], "SO") == 0 && line[1] && !line[2])
		so_parse(line[1], parse, game);
	else if (ft_strcmp(line[0], "WE") == 0 && line[1] && !line[2])
		we_parse(line[1], parse, game);
	else if (ft_strcmp(line[0], "EA") == 0 && line[1] && !line[2])
		ea_parse(line[1], parse, game);
	else if (ft_strcmp(line[0], "F") == 0 && line[1] && !line[2])
		f_parse(line[1], parse, game);
	else if (ft_strcmp(line[0], "C") == 0 && line[1] && !line[2])
		c_parse(line[1], parse, game);
}

void	parse_map(t_game *game, t_parse *parse)
{
	int		i;
	char	**tmp;

	i = 0;
	while (game->map[i])
	{
		if (game->map[i][0] == '\0')
		{
			i++;
			continue ;
		}
		if (game->map[i][0] == ' ' || game->map[i][0] == '1')
			break ;
		tmp = ft_split(game->map[i], ' ');
		if (!tmp)
			destroy_game_failure(game, "Memory allocation error.");
		parse_line(tmp, parse, game);
		free_split(tmp);
		tmp = NULL;
		i++;
	}
	if (!parse->no || !parse->so || !parse->we || !parse->ea
		|| !parse->f || !parse->c)
		destroy_game_failure(game, "Incomplete parsing.");
}
