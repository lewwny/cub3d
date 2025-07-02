/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   os.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:10:35 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/02 17:10:43 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef __linux__

void	free_linux(t_game *game)
{
	mlx_destroy_display(game->mlx_ptr);
}
#endif

#ifdef __APPLE__

void	free_linux(t_game *game)
{
	(void)game;
}

#endif