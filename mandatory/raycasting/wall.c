/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:29:29 by zbakkas           #+#    #+#             */
/*   Updated: 2024/10/06 16:15:43 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_args(t_arg_w *args, t_player *player, t_inst *p)
{
	args->check = false;
	player->texture_offset = 0;
	p->distance *= cos(args->ray_angle - player->angle);
	args->wall_height = (PEX / p->distance) * (WIDTH / 2) / tan(FOV / 2);
	args->wall_b = ((HEIGHT / 2) + (args->wall_height / 2)) + player->yy;
	args->wall_t = ((HEIGHT / 2) - (args->wall_height / 2)) + player->yy;
	if (args->wall_b > HEIGHT) 
		args->wall_b = HEIGHT;
	if (args->wall_t < 0)
	{
		args->check = true;
		args->tmp = (-args->wall_t) / args->wall_height;
		args->wall_t = 0;
	}
	args->sq = args->wall_t;
	player->wall_height = args->wall_height;
	player->wall_t = args->wall_t;
}

static void	render_wall1(t_player *player, t_arg_w args, t_fpoint p)
{
	if (player->is_vertical)
	{
		if (args.ray_angle > M_PI / 2.0 && args.ray_angle < 3 * M_PI / 1)
			args.color = load_colors(player, player->w_texter, p, args);
		if ((args.ray_angle > 3 * M_PI / 2.0 && args.ray_angle < 2 * M_PI)
			|| (args.ray_angle > 0 && args.ray_angle < M_PI / 2.0))
			args.color = load_colors(player, player->e_texter, p, args);
		mlx_put_pixel(player->img, args.i, args.wall_t, args.color);
	}
	else
	{
		if (args.ray_angle > M_PI && args.ray_angle < 2 * M_PI)
			args.color = load_colors(player, player->n_texter, p, args);
		else
			args.color = load_colors(player, player->s_texter, p, args);
		mlx_put_pixel(player->img, args.i, args.wall_t, args.color);
	}
}

void	render_wall(t_player *player, t_arg_w args, int flag, t_inst p)
{
	init_args(&args, player, &p);
	player->is_vertical = flag;
	while (args.wall_t < args.wall_b)
	{
		player->pos_y = args.wall_t;
		render_wall1(player, args, (t_fpoint){p.x, p.y});
		args.wall_t++;
	}
	if (args.wall_b <= 0)
		args.wall_b = 1;
	while (args.wall_b > 0 && args.wall_b < HEIGHT)
		mlx_put_pixel(player->img, args.i, args.wall_b++, player->color_floor);
	if (args.sq >= HEIGHT)
		args.sq = HEIGHT - 1;
	while ((args.sq > 0 && args.sq < HEIGHT))
		mlx_put_pixel(player->img, args.i, args.sq--, player->color_sky);
}
