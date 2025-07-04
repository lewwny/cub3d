/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   os.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:10:35 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/04 15:44:07 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef __linux__

void	free_linux(t_game *game)
{
	if (game->mlx_ptr)
		mlx_destroy_display(game->mlx_ptr);
}
#endif

#ifdef __APPLE__

void	free_linux(t_game *game)
{
	(void)game;
}

#endif