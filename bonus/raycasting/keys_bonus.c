/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:21:33 by zbakkas           #+#    #+#             */
/*   Updated: 2024/10/02 18:31:04 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void	key_mov(t_player *player, float x, float y)
{
	float	ray_x;
	float	ray_y;

	ray_x = player->x + x;
	ray_y = player->y + y;
	if (player->map[(int)(player->y / PEX)][(int)(ray_x / PEX)] != '1'
	&& player->map[(int)(ray_y / PEX)][(int)(player->x / PEX)] != '1'
	&& player->map[(int)(ray_y / PEX)][(int)(ray_x / PEX)] != '1')
	{
		if ((player->map[(int)(player->y / PEX)][(int)(ray_x / PEX)] != 'D'
		&& player->map[(int)(ray_y / PEX)][(int)(player->x / PEX)] != 'D'
		&& player->map[(int)(ray_y / PEX)][(int)(ray_x / PEX)] != 'D'))
		{
			player->x = ray_x;
			player->y = ray_y;
		}
	}
}

static void	key_mov_tow(t_player *player, float x, float y,
mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_W && keydata.action)
	{
		x = (cos(player->angle) * MOVE_SPEED);
		y = (sin(player->angle) * MOVE_SPEED);
		key_mov(player, x, y);
	}
	if (keydata.key == MLX_KEY_S && keydata.action)
	{
		x = (cos(player->angle) * -MOVE_SPEED);
		y = (sin(player->angle) * -MOVE_SPEED);
		key_mov(player, x, y);
	}
	if (keydata.key == MLX_KEY_A && keydata.action)
	{
		x = (cos(player->angle - M_PI / 2) * MOVE_SPEED);
		y = (sin(player->angle - M_PI / 2) * MOVE_SPEED);
		key_mov(player, x, y);
	}
	if (keydata.key == MLX_KEY_D && keydata.action)
	{
		x = (cos(player->angle + M_PI / 2) * MOVE_SPEED);
		y = (sin(player->angle + M_PI / 2) * MOVE_SPEED);
		key_mov(player, x, y);
	}
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_player	*player;
	float		x;
	float		y;

	player = (t_player *)param;
	x = 0;
	y = 0;
	key_mov_tow(player, x, y, keydata);
	if (keydata.key == MLX_KEY_O && keydata.action)
		check_door(player, 40);
	if (keydata.key == MLX_KEY_LEFT && keydata.action)
		player->angle += -RO * ROTATE_SPEED;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action)
		player->angle += RO * ROTATE_SPEED;
	if (keydata.key == MLX_KEY_UP && keydata.action && player->yy <= HEIGHT)
		player->yy += 15;
	if (keydata.key == MLX_KEY_DOWN && keydata.action && player->yy >= -HEIGHT)
		player->yy -= 15;
	if (keydata.key == MLX_KEY_SPACE && keydata.action)
		player->space = true;
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(0);
	if (keydata.key == MLX_KEY_LEFT_SHIFT)
		player->is_fire = true;
}

void	f_mouse( void *param)
{
	t_player	*player;
	int			xx;
	int			yy;

	player = (t_player *)param;
	xx = 0;
	yy = 0;
	mlx_get_mouse_pos(player->mlx, &xx, &yy);
	if (xx + 15 < WIDTH / 2)
		player->angle += -MOUSE_SENSITIVE * ROTATE_SPEED;
	else if (xx - 15 > WIDTH / 2)
		player->angle += MOUSE_SENSITIVE * ROTATE_SPEED;
	if (yy + 15 < HEIGHT / 2 && player->yy <= HEIGHT)
		player->yy += 30;
	else if (yy - 15 > HEIGHT / 2 && player->yy >= -HEIGHT)
		player->yy -= 30;
	mlx_set_mouse_pos(player->mlx, WIDTH / 2, HEIGHT / 2);
}

void	fire_(t_player *player)
{
	draw_gun(player, player->gun_texture[player->i_fire]);
	if (player->i_time > 1)
	{
		player->i_fire++;
		player->i_time = 0;
	}
	if (player->i_fire == 11)
	{
		player->i_fire = 0;
		player->is_fire = false;
	}
	player->i_time++;
}
