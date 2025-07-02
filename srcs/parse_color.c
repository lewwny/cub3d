/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:31:29 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/02 17:36:52 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_atoie(char *str, char **end)
{
	int		res;
	long	neg;
	int		tok;

	neg = 1;
	res = 0;
	tok = 0;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = neg * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
		tok = 1;
	}
	if (end)
		*end = str;
	if (!res && !tok)
		return (-1);
	return (res * neg);
}

static void	parse_rgb_values(char *color, t_game *game, int *rgb)
{
	char	*end;

	rgb[0] = ft_atoie(color, &end);
	if (*end != ',' || rgb[0] < 0 || rgb[0] > 255 || end == color)
		destroy_game_failure(game, "Invalid color format or value for R.");
	rgb[1] = ft_atoie(end + 1, &end);
	if (*end != ',' || rgb[1] < 0 || rgb[1] > 255 || end == color + 1)
		destroy_game_failure(game, "Invalid color format or value for G.");
	rgb[2] = ft_atoie(end + 1, &end);
	if (*end != '\0' || rgb[2] < 0 || rgb[2] > 255 || end == color + 2)
		destroy_game_failure(game, "Invalid color format or value for B.");
}

static void	check_color_format(char *color, t_game *game, int tok)
{
	int	rgb[3];

	parse_rgb_values(color, game, rgb);
	if (!tok)
	{
		game->color.floor.r = rgb[0];
		game->color.floor.g = rgb[1];
		game->color.floor.b = rgb[2];
	}
	else
	{
		game->color.ceiling.r = rgb[0];
		game->color.ceiling.g = rgb[1];
		game->color.ceiling.b = rgb[2];
	}
}

void	f_parse(char *color, t_parse *parse, t_game *game)
{
	if (parse->f)
		destroy_game_failure(game, "Duplicate F token in parsing.");
	if (!color)
		destroy_game_failure(game, "F color is NULL in parsing.");
	else
	{
		check_color_format(color, game, 0);
		parse->f = 1;
		parse->f_color = ft_strdup(color, &game->garbage);
	}
}

void	c_parse(char *color, t_parse *parse, t_game *game)
{
	if (parse->c)
		destroy_game_failure(game, "Duplicate C token in parsing.");
	if (!color)
		destroy_game_failure(game, "C color is NULL in parsing.");
	else
	{
		check_color_format(color, game, 1);
		parse->c = 1;
		parse->c_color = ft_strdup(color, &game->garbage);
	}
}
