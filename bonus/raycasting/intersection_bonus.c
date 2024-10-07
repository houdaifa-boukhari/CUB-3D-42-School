/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:10:04 by zbakkas           #+#    #+#             */
/*   Updated: 2024/10/02 18:31:01 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

typedef struct s_int_
{
	double	ya;
	double	xa;
}			t_int_;

static int	if_(t_player *player, t_inst *int_)
{
	if ((int)(int_->y / PEX) < player->map_height && 
	((int)(int_->x / PEX)) < (int)ft_strlen(player->map[(int)(int_->y / PEX)]) 
	&& (player->map[(int)(int_->y / PEX)][(int)(int_->x / PEX)] == '1'
	|| (player->map[(int)(int_->y / PEX)][(int)(int_->x / PEX)] == 'D' 
	|| (player->map[(int)(int_->y / PEX)][(int)(int_->x / PEX)] == 'd'))))
		return (1);
	return (0);
}

static int	int__(t_player *player, t_inst *int_,
bool is_door, t_int_ arg)
{
	while ((int)(int_->x / PEX) >= 0 && 
	(int)(int_->x / PEX) <= player->map_weidth && 
	(int)(int_->y / PEX) >= 0 && (int)(int_->y / PEX) <= player->map_height)
	{
		if (if_(player, int_))
		{
			if (player->map[(int)(int_->y / PEX)][(int)(int_->x / PEX)] == 'd'
				&& is_door)
			{
				int_->x += arg.xa;
				int_->y += arg.ya;
			}
			else
				return (int_->distance = (sqrt(pow(int_->x - player->x, 2) 
							+ pow(int_->y - player->y, 2))), 0);
		}
		else
		{
			int_->x += arg.xa;
			int_->y += arg.ya;
		}
	}
	return (0);
}

t_inst	get_h(t_player *player, double ray_angle, bool is_door)
{
	t_inst	int_;
	double	first_y;
	double	first_x;
	t_int_	arg;

	int_.distance = 99999999999999;
	if (ray_angle > 0 && ray_angle < M_PI)
		first_y = (floor(player->y / PEX) * PEX) + PEX;
	else
		first_y = (floor(player->y / PEX) * PEX) - 0.00001;
	first_x = player->x + ((first_y - player->y) / tan(ray_angle));
	int_.x = first_x;
	int_.y = first_y;
	if (ray_angle > 0 && ray_angle < M_PI)
		arg.ya = PEX;
	else
		arg.ya = -PEX;
	arg.xa = arg.ya / tan(ray_angle);
	int__(player, &int_, is_door, arg);
	return (int_);
}

t_inst	get_v(t_player *player, double ray_angle, bool is_door)
{
	t_inst	int_;
	double	first_x;
	double	first_y;
	t_int_	arg;

	int_.distance = 99999999999999;
	if (!(ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2))
		first_x = (floor(player->x / PEX) * PEX) + PEX;
	else
		first_x = (floor(player-> x / PEX) * PEX) - 0.001;
	first_y = player->y + (first_x - player->x) * tan(ray_angle);
	int_.x = first_x;
	int_.y = first_y;
	if (!(ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2))
		arg.xa = PEX;
	else
		arg.xa = -PEX;
	arg.ya = arg.xa * tan(ray_angle);
	int__(player, &int_, is_door, arg);
	return (int_);
}
