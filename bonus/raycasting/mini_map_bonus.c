/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:19:05 by zbakkas           #+#    #+#             */
/*   Updated: 2024/10/02 18:31:08 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

typedef struct s_args_map
{
	double	x;
	double	y;
	int		h ;
	int		v ;
	double	start_y;
	double	end_y;
	double	start_x;
	double	end_x ;
}			t_args_map;

static void	cader_map_tow(t_player *player, int c_m_y,
int max_c_m_y, int max_c_m_x)
{
	while (c_m_y < max_c_m_y)
	{
		mlx_put_pixel(player->img, 0, c_m_y, 0xFF0000FF);
		mlx_put_pixel(player->img, 1, c_m_y, 0xFF0000FF);
		mlx_put_pixel(player->img, 2, c_m_y++, 0xFF0000FF);
	}
	c_m_y = 0;
	while (c_m_y < max_c_m_y)
	{
		mlx_put_pixel(player->img, max_c_m_x, c_m_y, 0xFF0000FF);
		mlx_put_pixel(player->img, max_c_m_x - 1, c_m_y, 0xFF0000FF);
		mlx_put_pixel(player->img, max_c_m_x - 2, c_m_y++, 0xFF0000FF);
	}
}

static void	cader_map(t_player *player, int h, int v)
{
	int	max_c_m_x;
	int	max_c_m_y;
	int	c_m_x;
	int	c_m_y ;

	max_c_m_x = (h * 2);
	max_c_m_y = (v * 2);
	c_m_x = 0;
	c_m_y = 0;
	while (c_m_x < max_c_m_x)
	{
		mlx_put_pixel(player->img, c_m_x, 0, 0xFF0000FF);
		mlx_put_pixel(player->img, c_m_x, 1, 0xFF0000FF);
		mlx_put_pixel(player->img, c_m_x++, 2, 0xFF0000FF);
	}
	c_m_x = 0;
	while (c_m_x < max_c_m_x)
	{
		mlx_put_pixel(player->img, c_m_x, max_c_m_y, 0xFF0000FF);
		mlx_put_pixel(player->img, c_m_x, max_c_m_y - 1, 0xFF0000FF);
		mlx_put_pixel(player->img, c_m_x++, max_c_m_y - 2, 0xFF0000FF);
	}
	cader_map_tow(player, c_m_y, max_c_m_y, max_c_m_x);
}

static void	put_p(t_player *player, t_args_map args, uint32_t color)
{
	mlx_put_pixel(player->img, args.start_x - (args.x - args.h),
		args.start_y - (args.y - args.v), color);
}

static void	mini_map_tow(t_player *player, t_args_map args)
{
	if ((args.start_x / (PEX / 2)) >= 0 && (args.start_y / (PEX / 2)) >= 0
		&& (args.start_y / (PEX / 2)) < player->map_height && 
		(args.start_x / (PEX / 2)) < 
		(int)ft_strlen(player->map[(int)(args.start_y / (PEX / 2))]) 
		&& player->map[(int)(args.start_y / (PEX / 2))]
		[(int)(args.start_x / (PEX / 2))] == '1')
		put_p(player, args, 0xFFFFFFFF);
	else if ((args.start_x / (PEX / 2)) >= 0 && (args.start_y / (PEX / 2)) >= 0
		&& (args.start_y / (PEX / 2)) < player->map_height && 
		(args.start_x / (PEX / 2)) 
		< (int)ft_strlen(player->map[(int)(args.start_y / (PEX / 2))]) 
		&& player->map[(int)(args.start_y / (PEX / 2))]
		[(int)(args.start_x / (PEX / 2))] == 'D')
		put_p(player, args, 0xFF0000FF);
	else if ((args.start_x / (PEX / 2)) >= 0 && (args.start_y / (PEX / 2)) >= 0 
		&& (args.start_y / (PEX / 2)) < player->map_height && 
		(args.start_x / (PEX / 2)) 
		< (int)ft_strlen(player->map[(int)(args.start_y / (PEX / 2))]) 
		&& player->map[(int)(args.start_y / (PEX / 2))]
		[(int)(args.start_x / (PEX / 2))] == 'd')
		put_p(player, args, 0xFFFFFFF);
	else
		put_p(player, args, 0x000000FF);
}

void	mini_map(t_player *player)
{
	t_args_map	args;

	args.x = player->x / 2;
	args.y = player->y / 2;
	args.h = 8 * (PEX / 2);
	args.v = 6 * (PEX / 2);
	args.start_y = args.y - args.v;
	args.end_y = args.y + args.v;
	while (args.start_y < args.end_y)
	{
		args.start_x = args.x - args.h;
		args.end_x = args.x + args.h;
		while (args.start_x < args.end_x)
		{
			mini_map_tow(player, args);
			args.start_x++;
		}
		args.start_y++;
	}
	cader_map(player, args.h, args.v);
	draw_player(player, args.v, args.h);
}
