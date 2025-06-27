/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:31:29 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/27 15:45:34 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	f_parse(char *color, t_parse *parse, t_game *game)
{
	if (parse->f)
		destroy_game_failure(game, "Duplicate F token in parsing.");
	if (!color)
		destroy_game_failure(game, "F color is NULL in parsing.");
	else
	{
		parse->f = 1;
		parse->f_color = ft_strdup(color);
		if (!parse->f_color)
			destroy_game_failure(game, "Memory allocation error for F color.");
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
		parse->c = 1;
		parse->c_color = ft_strdup(color);
		if (!parse->c_color)
			destroy_game_failure(game, "Memory allocation error for C color.");
	}
}
