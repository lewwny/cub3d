/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:20:39 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/27 15:50:34 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	args_count(int argc)
{
	if (argc < 2)
	{
		ft_dprintf(2, "Error: Not enough arguments.\n");
		exit(EXIT_FAILURE);
	}
	else if (argc > 2)
	{
		ft_dprintf(2, "Error: Too many arguments.\n");
		exit(EXIT_FAILURE);
	}
}

static void	file_format(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(&filename[len - 4], ".cub", 4) != 0)
	{
		ft_dprintf(2, "Error: Invalid file format. Expected .cub file.\n");
		exit(EXIT_FAILURE);
	}
}

void	parsing(int argc, char **argv, t_game *game)
{
	(void) game;
	args_count(argc);
	file_format(argv[1]);
	extract_map(argv[1], game);
	parse_map(game, &game->parse);
}
