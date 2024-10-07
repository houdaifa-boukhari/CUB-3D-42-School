/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:27:45 by zbakkas           #+#    #+#             */
/*   Updated: 2024/10/06 16:20:43 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

typedef struct s_arg_door
{
	double	wall_height;
	double	wall_b;
	double	wall_t;
	double	sq;
	bool	check;
	t_int	color;
	double	tmp;
}			t_arg_door;

void	draw_player(t_player *player, int v, int h)
{
	int		ii;
	double	an_x;
	double	an_y;

	ii = 0;
	mlx_put_pixel(player->img, h, v, 0xFF0000FF);
	mlx_put_pixel(player->img, h + 1, v, 0xFF0000FF);
	mlx_put_pixel(player->img, h - 1, v, 0xFF0000FF);
	mlx_put_pixel(player->img, h, v + 1, 0xFF0000FF);
	mlx_put_pixel(player->img, h, v - 1, 0xFF0000FF);
	mlx_put_pixel(player->img, h + 1, v + 1, 0xFF0000FF);
	mlx_put_pixel(player->img, h - 1, v - 1, 0xFF0000FF);
	mlx_put_pixel(player->img, h + 1, v - 1, 0xFF0000FF);
	mlx_put_pixel(player->img, h - 1, v + 1, 0xFF0000FF);
	while (ii < 10)
	{
		an_x = h + (cos(normal_ang(player->angle)) * ii);
		an_y = v + (sin(normal_ang(player->angle)) * ii);
		mlx_put_pixel(player->img, an_x, an_y, 0xFF0000FF);
		ii++;
	}
}

void	render_door_tow(t_player *player, t_arg_door arg, t_inst inst, int i)
{
	t_arg_w	args;

	args.check = false;
	if ((inst.y >= 0 && inst.x >= 0 && (int)(inst.y / PEX) < player->map_height
		&& (int)(inst.x / PEX) < player->map_weidth)
		&& player->map[(int)(inst.y / PEX)][(int)(inst.x / PEX)] == 'd')
	{
		while (arg.wall_t < arg.wall_b)
		{
			player->pos_y = arg.wall_t;
			if (arg.check)
				player->texture_offset = arg.tmp
					* player->door_open_tex->height;
			arg.color = load_colors(player, player->door_open_tex,
					(t_fpoint){inst.x, inst.y}, args);
			if (arg.color)
				mlx_put_pixel(player->img, i, arg.wall_t, arg.color);
			arg.wall_t++;
		}
	}
}

void	render_door(t_player *player, t_arg_w args_w, int flag, t_inst inst)
{
	t_arg_door	arg;

	arg.check = false;
	player->texture_offset = 0;
	inst.distance *= cos(args_w.ray_angle - player->angle);
	arg.wall_height = (PEX / inst.distance)
		* (WIDTH / 2) / tan(FOV / 2);
	arg.wall_b = ((HEIGHT / 2) + (arg.wall_height / 2)) + player->yy;
	arg.wall_t = ((HEIGHT / 2) - (arg.wall_height / 2)) + player->yy;
	if (arg.wall_b > HEIGHT) 
		arg.wall_b = HEIGHT;
	if (arg.wall_t < 0)
	{
		arg.check = true;
		arg.tmp = (-arg.wall_t) / arg.wall_height;
		arg.wall_t = 0;
	}
	arg.sq = arg.wall_t;
	player->wall_height = arg.wall_height;
	player->wall_t = arg.wall_t;
	player->is_vertical = flag;
	render_door_tow(player, arg, inst, args_w.i);
}

int	check_door(t_player *player, int distance)
{
	int			i;
	t_fpoint	p;

	i = 0;
	while (++i <= distance)
	{
		p.x = player->x + cos(normal_ang(player->angle)) * i;
		p.y = player->y + sin(normal_ang(player->angle)) * i;
		if (p.x < 0 || p.y < 0 || ((int)(p.y / PEX) >= player->map_height
			|| (int)(p.x / PEX) >= player->map_weidth))
			return (0);
		if (player->map[(int)(p.y / PEX)][(int)(p.x / PEX)] == 'D' 
		&& player->map[(int)(player->y / PEX)][(int)(player->x / PEX)] != 'D')
		{
			player->map[(int)(p.y / PEX)][(int)(p.x / PEX)] = 'd';
			return (1);
		}
		else if (player->map[(int)(p.y / PEX)][(int)(p.x / PEX)] == 'd'
		&& player->map[(int)(player->y / PEX)][(int)(player->x / PEX)] != 'd')
		{
			player->map[(int)(p.y / PEX)][(int)(p.x / PEX)] = 'D';
			return (2);
		}
	}
	return (0);
}
