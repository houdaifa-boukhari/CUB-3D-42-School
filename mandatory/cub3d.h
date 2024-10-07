/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:33:50 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/10/02 19:53:59 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define PI 3.14
# define V_CH " 10NSEW"
# define P_PLAYER "NSEW"
# define ERR_CH "Invalid character or you have more than one player"
# define NOT_EXIST "Map not exist"
# define MAP_ERR "map is not sourounded or closed"
# define MAP_V "MAP is not valid"
# define PY_ERR "ERR dont have Player"
# define POS_DOOR "DOOR :: BAD Position"

typedef unsigned int	t_int;

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_door
{
	int		x;
	int		y;
	bool	open_door;
}			t_door;

typedef struct s_fpoint
{
	double	x;
	double	y;
}			t_fpoint;

typedef struct s_map
{
	char			*row;
	int				s_x;
	struct s_map	*prev;
	struct s_map	*next;
}					t_map;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

typedef struct s_inf
{
	char	**inf_map;
	char	*n_path;
	char	*s_path;
	char	*e_path;
	char	*w_path;
	char	*f_color;
	char	*c_color;
	char	position;
	int		color_c;
	int		color_f;
}			t_inf;

typedef struct s_player
{
	char			**map;
	float			x;
	float			y;
	int				map_height;
	int				map_weidth;
	double			texture_offset;
	unsigned int	color_sky;
	unsigned int	color_floor;
	double			angle;
	t_door			*door_p;
	mlx_image_t		*img;
	mlx_t			*mlx;
	int				yy;
	bool			space;
	bool			is_vertical;
	int				time_space;
	bool			player_up;
	bool			player_down;
	double			wall_t;
	double			wall_b;
	double			pos_y;
	double			wall_height;
	int				start_mouse;
	mlx_texture_t	*n_texter;
	mlx_texture_t	*s_texter;
	mlx_texture_t	*e_texter;
	mlx_texture_t	*w_texter;
	mlx_texture_t	*door_tex;
	mlx_texture_t	*door_open_tex;
	mlx_texture_t	**gun_texture;
	bool			is_fire;
	int				i_fire;
	int				i_time;
}					t_player;

typedef struct s_intersection
{
	double	distance;
	double	x;
	double	y;
}			t_inst;

typedef struct s_args_render_wall
{
	double	wall_height;
	double	wall_b;
	double	wall_t;
	double	sq;
	bool	check;
	t_int	color;
	double	tmp;
	double	ray_angle;
	int		i;
}			t_arg_w;

// all function for paring

int		get_max(t_map *map);
void	free_inf(t_inf *inf);
void	free_map(t_map **map);
bool	check_errors(t_inf *inf);
bool	valide_path(char **path);
bool	check_map_err(t_map *map);
char	**built2darray(t_map *map);
int		count_charcter(char **str, char c);
void	initialize_inf(t_inf *inf);
void	back_to_default(char **map, char c);
void	print_information(t_inf inf);
int		count_exist_line(t_map *map);
void	take_map(t_map **map, int fd);
void	valide_arg(char *file, int *fd);
void	parsing_information(t_inf *inf);
bool	map_isclosed(char **map, char c, t_point **point);
bool	valid_ch(t_map *map, t_inf *inf);
t_map	*get_position(t_map *map, int idx);
void	find_start(t_map *map, char *line);
void	creat_list(t_map **map, char *line);
t_point	find_empty_space(char **map, char c);
bool	flood_fill(char **tab, t_point begin);
bool	catch_color(char *p_color, int *n_color);
void	take_information(t_map *map, t_inf *inf);
t_point	*get_position_door(char **map);
char	*fill_spaces(char *str, int len, int size);
bool	valid_door(char **map, t_point *point);
bool	check_wall(char **map, t_point begin, t_point size);
void	draw_gun(t_player *player, mlx_texture_t *texture);
bool	door_is_s(t_point **p, char **map);
void	free_textures(t_player *player);
void	init_texutres_data(t_player *player);
void	free_content_tex(t_player *player);
bool	init_gun_tex(t_player *player);
bool	assign_player(t_player *player, char **map, t_inf inf);
t_int	load_colors(t_player *player, mlx_texture_t *texture, 
			t_fpoint x, t_arg_w args);
// all function for recasting

# define MOVE_SPEED 10
// ROTATE_SPEED (10 * (M_PI / 180)) // 0.01745329252 =>> 0.1745329252
# define ROTATE_SPEED 0.174533
// FOV 60 * (M_PI / 180) // 60 degrees field of view (FOV) in radians
# define FOV 1.047198
# define PEX 32
# define HEIGHT 1200
# define WIDTH 1500
# define NUM_RAYS 1500
# define MOUSE_SENSITIVE 0.7
# define RO 1

void	init_all_data(char **av, t_player *player);
void	mini_map(t_player *player);
void	my_keyhook(mlx_key_data_t keydata, void *param);
void	f_mouse(void *param);
void	fire_(t_player *player);
void	draw_player(t_player *player, int v, int h);
void	render_wall(t_player *player, t_arg_w args, int flag, t_inst p);
float	normal_ang(double angle);
t_inst	get_h(t_player *player, double ray_angle, bool is_door);
t_inst	get_v(t_player *player, double ray_angle, bool is_door);

#endif
