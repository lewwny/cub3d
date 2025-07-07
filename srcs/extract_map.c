/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:37:10 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/07 19:02:19 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	fill_tmp(int *i, char **map, char **tmp, int *count)
{
	*i = 0;
	while (*i < *count)
	{
		tmp[*i] = map[*i];
		(*i)++;
	}
	tmp[*i] = NULL;
}

static char	**read_file(int fd, t_game *game)
{
	char	**map;
	char	*line;
	int		count;
	int		i;
	char	**tmp;

	map = NULL;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		tmp = _malloc(sizeof(char *) * (count + 2), &game->garbage);
		if (!tmp)
			malloc_error(&game->garbage);
		fill_tmp(&i, map, tmp, &count);
		tmp[count] = line;
		tmp[count + 1] = NULL;
		if (map)
			_free(map, &game->garbage);
		map = tmp;
		count++;
		line = get_next_line(fd);
	}
	return (map);
}

static void	truncate_newline(char **map)
{
	int	i;
	int	len;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > 0 && map[i][len - 1] == '\n')
			map[i][len - 1] = '\0';
		i++;
	}
}

void	extract_map(char *filename, t_game *game)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, "Error: Could not open file %s.\n", filename);
		exit(EXIT_FAILURE);
	}
	game->map = read_file(fd, game);
	if (!game->map || !game->map[0])
		destroy_game_failure(game, "Map is empty or invalid.");
	truncate_newline(game->map);
}
