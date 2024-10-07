/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainn_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:54:47 by zbakkas           #+#    #+#             */
/*   Updated: 2024/10/02 19:52:59 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

float	normal_ang(double angle)
{
	angle = fmod(angle, M_PI * 2);
	if (angle < 0)
		angle = M_PI * 2 + angle;
	return (angle);
}

static void	draw_rays(t_player *player)
{
	t_inst	distance_h;
	t_inst	distance_v;
	t_arg_w	args;

	args.i = -1;
	args.ray_angle = (normal_ang(player->angle) - FOV / 2);
	while (++args.i < NUM_RAYS)
	{
		args.ray_angle = normal_ang(args.ray_angle);
		distance_h = get_h(player, args.ray_angle, 1);
		distance_v = get_v(player, args.ray_angle, 1);
		if (distance_v.distance < distance_h.distance)
			render_wall(player, args, 1, distance_v);
		else
			render_wall(player, args, 0, distance_h);
		distance_h = get_h(player, args.ray_angle, 0);
		distance_v = get_v(player, args.ray_angle, 0);
		if (distance_v.distance < distance_h.distance)
			render_door(player, args, 1, distance_v);
		else
			render_door(player, args, 0, distance_h);
		args.ray_angle += (FOV / NUM_RAYS);
	}
}

static void	jump(t_player *player)
{
	if (player->space && player->time_space >= 0 && !player->player_up)
	{
		player->yy += 15;
		player->time_space--;
	}
	if (player->space && player->time_space >= 0 && player->player_up)
	{
		player->yy -= 15;
		player->time_space--;
	}
	if (player->time_space < 0 && !player->player_up)
	{
		player->player_up = true;
		player->time_space = 12;
	}
	if (player->time_space < 0 && player->player_up && player->space)
	{
		player->player_up = false;
		player->space = false;
		player->time_space = 12;
	}
}

static void	game_loop(void *param)
{
	t_player	*player;

	player = (t_player *)param;
	mlx_delete_image(player->mlx, player->img);
	player->img = mlx_new_image(player->mlx, 1500, 1200);
	mlx_image_to_window(player->mlx, player->img, 0, 0);
	mlx_key_hook(player->mlx, my_keyhook, player);
	jump(player);
	draw_rays(player);
	mini_map(player);
	if (player->start_mouse-- < 0)
	{
		f_mouse(player);
		player->start_mouse = -1;
	}
	else
		mlx_set_mouse_pos(player->mlx, WIDTH / 2, HEIGHT / 2);
	if (player->is_fire)
		fire_(player);
	else
		draw_gun(player, player->gun_texture[0]);
}

int	main(int arc, char **arv)
{
	t_player	player;

	if (arc != 2)
	{
		ft_putendl_fd("Use ./cub3D file.cub", STDERR_FILENO);
		exit(0);
	}
	init_texutres_data(&player);
	init_all_data(arv, &player);
	player.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	player.gun_image = mlx_new_image(player.mlx, WIDTH, HEIGHT);
	player.img = mlx_new_image(player.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(player.mlx, player.img, 0, 0);
	mlx_set_cursor_mode(player.mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(player.mlx, game_loop, &player);
	mlx_loop(player.mlx);
	free_arrays(player.map);
	free_textures(&player);
	return (0);
}
