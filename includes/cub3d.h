/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:24:23 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/26 18:02:11 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx_mac/mlx.h"

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
	char	*map;
	t_gb	*garbage;
}	t_game;

#endif