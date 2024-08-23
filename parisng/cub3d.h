#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

typedef struct s_map
{
	char			*row;
	int				s_x;
	struct s_map	*prev;
	struct s_map	*next;
}   				t_map;

typedef struct s_color
{
	int r;
	int g;
	int b;
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

void	free_inf(t_inf	inf);
bool	check_errors(t_inf inf);
void    initialize_inf(t_inf *inf);
void    take_map(t_map **map, int fd);
void	valide_arg(char *file, int *fd);
void	parsing_information(t_inf *inf);
void    take_information(t_map *map, t_inf *inf);
void	find_start(t_map *map, char	*line);
void	creat_list(t_map **map, char *line);

#endif