/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:24:23 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/02 15:16:08 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>

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
#  define LINUX 0
#  include "../mlx_mac/mlx.h"

# elif __linux__

#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_ESC 65307
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define LINUX 1
#  include "../mlx_linux/mlx.h"

# endif

typedef struct s_parse
{
	int		no;
	char	*no_path;
	int		so;
	char	*so_path;
	int		we;
	char	*we_path;
	int		ea;
	char	*ea_path;
	int		f;
	char	*f_color;
	int		c;
	char	*c_color;
}	t_parse;

typedef struct s_ceiling
{
	int	r;
	int	g;
	int	b;
}	t_ceiling;

typedef struct s_floor
{
	int	r;
	int	g;
	int	b;
}	t_floor;

typedef struct s_color
{
	t_ceiling	ceiling;
	t_floor		floor;
} t_color;

typedef struct s_player
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
}	t_player;

typedef struct s_texture
{
	void	*no;
	void	*so;
	void	*we;
	void	*ea;
}	t_texture;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*menu;
	void		*menu2;
	void		*menu3;
	int			width;
	int			height;
	int			menu_mode;
	char		**map;
	char		**tmp;
	char		**final_map;
	t_gb		*garbage;
	t_parse		parse;
	t_player	player;
	t_texture	texture;
}	t_game;

void	parsing(int argc, char **argv, t_game *game);
void	destroy_game(t_game *game);
void	load_img(t_game *game);
void	extract_map(char *filename, t_game *game);
void	print_map(char **map);
void	init_parse(t_parse *parse);
void	destroy_game_failure(t_game *game, const char *message);
void	free_split(char **split);
void	parse_map(t_game *game, t_parse *parse);
void	map_to_finalmap(t_game *game, int i);
void	parse_finalmap(t_game *game);
void	free_oldmap(char **map, t_gb **garbage);
void	move_player(t_game *game, int keycode);
void	extract_texture(t_game *game);

//TEXTURE COLOR PARSING
void	no_parse(char *filename, t_parse *parse, t_game *game);
void	so_parse(char *filename, t_parse *parse, t_game *game);
void	we_parse(char *filename, t_parse *parse, t_game *game);
void	ea_parse(char *filename, t_parse *parse, t_game *game);
void	f_parse(char *color, t_parse *parse, t_game *game);
void	c_parse(char *color, t_parse *parse, t_game *game);
void	init_player(t_game *game);

//MLX HOOKS
int		key_hook(int keycode, t_game *game);
int		on_mouse_move(int x, int y, t_game *game);
int		on_mouse_click(int button, int x, int y, t_game *game);

#endif