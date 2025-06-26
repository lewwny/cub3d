/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:24:23 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/06/26 20:23:44 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx_mac/mlx.h"
# include <stdio.h>

# define WIDTH 1280
# define HEIGHT 720

# ifdef __APPLE__ 

#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124

# elif __linux__

#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_ESC 65307
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363

# endif

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*menu;
	void	*menu2;
	void	*menu3;
	int		width;
	int		height;
	int		menu_mode;
	char	*map;
	t_gb	*garbage;
}	t_game;

void	parsing(int argc, char **argv, t_game *game);
void	destroy_game(t_game *game);
void	load_img(t_game *game);

int		key_hook(int keycode, t_game *game);
int		on_mouse_move(int x, int y, t_game *game);
int		on_mouse_click(int button, int x, int y, t_game *game);

#endif