/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:24:23 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/09 16:18:18 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <sys/types.h>
# include <pthread.h>

# define WIDTH 1280
# define HEIGHT 720

# define NO_SO 0
# define WE_EA 1

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define PORT 8080
# define BUFFER_SIZE 20000

# ifdef __APPLE__ 

#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define LINUX 0
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_SHIFT 257
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
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_SHIFT 65505
#  include "../mlx_linux/mlx.h"

# endif

typedef struct s_server
{
	int					server_fd;
	int					client_fd;
	struct sockaddr_in	server_addr;
	struct sockaddr_in	client_addr;
	socklen_t			addr_len;
	pthread_mutex_t		mutex;
}	t_server;

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
}	t_color;

typedef struct s_wall
{
	int				height;
	int				start;
	int				end;
	int				side;
	int				color;
	double			wall_x;
	double			step;
	double			tex_pos;
	int				tex_x;
	int				tex_y;
	unsigned int	*data;
}	t_wall;

typedef struct s_ray
{
	double	camera_x;
	double	ray_x;
	double	ray_y;
	double	stepsize;
	double	step_size_x;
	double	step_size_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	distance;
	double	wall_x;
	int		mapx;
	int		mapy;
	double	side_dist_x;
	double	side_dist_y;
	int		side;
	bool	hit;
	t_wall	wall;
}	t_ray;

typedef struct s_player
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	fov;
	double	target_fov;
	double	move_speed;
	int		pitch;
	t_ray	ray;
}	t_player;

typedef struct s_tex_data
{
	int				width;
	int				height;
	int				endian;
	int				bpp;
	int				size_line;
	unsigned int	*data;
}	t_tex_data;

typedef struct s_texture
{
	void			*no;
	void			*so;
	void			*we;
	void			*ea;
	unsigned int	*no_data;
	unsigned int	*so_data;
	unsigned int	*we_data;
	unsigned int	*ea_data;
	t_tex_data		tex_ptr[4];
}	t_texture;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
	int		up;
	int		down;
	int		esc;
	int		shift;
}	t_keys;

typedef struct s_menu
{
	void		*resume2;
	void		*quit2;
}	t_menu;

typedef struct s_other
{
	double	otherposx;
	double	otherposy;
	double	posx;
	double	posy;
}	t_other;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*menu;
	void		*menu2;
	void		*menu3;
	void		*buftmp;
	void		*pause_menu;
	void		*resume;
	void		*quit;
	int			*buf;
	int			width;
	int			height;
	int			menu_mode;
	int			line_len;
	int			bpp;
	int			endian;
	int			host;
	int			join;
	int			sock;
	double		delta_time;
	char		**map;
	char		**tmp;
	char		**final_map;
	t_gb		*garbage;
	t_parse		parse;
	t_player	player;
	t_texture	texture;
	t_color		color;
	t_keys		keys;
	t_menu		menuimg;
	t_server	server;
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
void	convert_texture(t_game *game);
void	raycasting(t_game *game);
void	pause_menu(t_game *game);
void	update_pause_menu(t_game *game, int new_menu_mode);
void	quit_game(t_game *game);
void	mouse_show(t_game *game);
void	mouse_hide(t_game *game);
void	mouse_move(t_game *game, int x, int y);
int		rotate_player_by_mouse(t_game *game, int delta_x, int delta_y);
double	get_delta_time(void);
void	sprint_off(t_game *game);
void	sprint_on(t_game *game);
void	fov_sprint(t_game *game);
void	handle_sprint(t_game *game);
void	init_server(t_game *game);
void	close_server(t_game *game);
void	*server_thread(void *game);
void	join_server(t_game *game, char **argv);
t_other	*_other(void);

//TEXTURE COLOR PARSING
void	no_parse(char *filename, t_parse *parse, t_game *game);
void	so_parse(char *filename, t_parse *parse, t_game *game);
void	we_parse(char *filename, t_parse *parse, t_game *game);
void	ea_parse(char *filename, t_parse *parse, t_game *game);
void	f_parse(char *color, t_parse *parse, t_game *game);
void	c_parse(char *color, t_parse *parse, t_game *game);
void	init_player(t_game *game);
void	init_keys(t_keys *keys);
void	free_linux(t_game *game);

//MLX HOOKS
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		game_loop(t_game *game);
int		on_mouse_move(int x, int y, t_game *game);
int		on_mouse_click(int button, int x, int y, t_game *game);

//INIT FUNCTIONS
void	init_sides(t_game *game, double raydirx, double raydiry);
void	perform_dda(t_game *game);
void	set_sides(t_game *game);
void	color_sides(t_game *game, int x, int y);
void	set_texture(t_game *game, double raydirx, double raydiry);
void	draw_wall_textured(t_game *game, int x, int y);
void	calculate_y_tex(t_game *game);

#endif
