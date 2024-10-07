/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:36:02 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/10/02 19:53:25 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_content_tex(t_player *player)
{
	if (player->n_texter)
		free(player->n_texter->pixels);
	if (player->s_texter)
		free(player->s_texter->pixels);
	if (player->e_texter)
		free(player->e_texter->pixels);
	if (player->w_texter)
		free(player->w_texter->pixels);
	if (player->door_tex)
		free(player->door_tex->pixels);
	if (player->door_open_tex)
		free(player->door_open_tex->pixels);
	free(player->n_texter);
	free(player->s_texter);
	free(player->e_texter);
	free(player->w_texter);
	free(player->door_tex);
	free(player->door_open_tex);
}

void	init_texutres_data(t_player *player)
{
	player->gun_texture = NULL;
	player->n_texter = NULL;
	player->s_texter = NULL;
	player->e_texter = NULL;
	player->w_texter = NULL;
	player->door_tex = NULL;
	player->door_open_tex = NULL;
	player->yy = 0;
	player->i_fire = 0;
	player->i_time = 0;
	player->space = false;
	player->time_space = 12;
	player->player_down = true;
	player->player_up = false;
	player->start_mouse = 15;
}

bool	init_gun_tex(t_player *player)
{
	player->gun_texture = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *)
			* 12);
	if (!player->gun_texture)
		return (false);
	player->gun_texture[0] = mlx_load_png("./textures/GUN/shoo0.png");
	player->gun_texture[1] = mlx_load_png("./textures/GUN/shoo5.png");
	player->gun_texture[2] = mlx_load_png("./textures/GUN/shoo6.png");
	player->gun_texture[3] = mlx_load_png("./textures/GUN/shoo4.png");
	player->gun_texture[4] = mlx_load_png("./textures/GUN/shoo3.png");
	player->gun_texture[5] = mlx_load_png("./textures/GUN/shoo2.png");
	player->gun_texture[6] = mlx_load_png("./textures/GUN/shoo1.png");
	player->gun_texture[7] = mlx_load_png("./textures/GUN/shoo1.png");
	player->gun_texture[8] = mlx_load_png("./textures/GUN/shoo2.png");
	player->gun_texture[9] = mlx_load_png("./textures/GUN/shoo3.png");
	player->gun_texture[10] = mlx_load_png("./textures/GUN/shoo4.png");
	player->gun_texture[11] = NULL;
	if (!player->gun_texture[0] || !player->gun_texture[1]
		|| !player->gun_texture[2] || !player->gun_texture[3]
		|| !player->gun_texture[4] || !player->gun_texture[5]
		|| !player->gun_texture[6] || !player->gun_texture[7]
		|| !player->gun_texture[8] || !player->gun_texture[9]
		|| !player->gun_texture[10])
		return (false);
	return (true);
}
