/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   os_mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:52:28 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/04 20:53:22 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef __APPLE__

void	mouse_show(t_game *game)
{
	(void)game;
}

void	mouse_hide(t_game *game)
{
	(void)game;
}

#endif

#ifdef __linux__

void	mouse_show(t_game *game)
{
	mlx_mouse_show(game->mlx_ptr, game->win_ptr);
}

void	mouse_hide(t_game *game)
{
	mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
}

#endif