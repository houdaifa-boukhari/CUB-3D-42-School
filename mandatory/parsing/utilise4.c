/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:43:32 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/10/01 10:50:01 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	door_is_s(t_point **p, char **map)
{
	int		i;
	t_point	*point;

	i = 0;
	point = *p;
	while (point[i].x != -1 && point[i].y != -1)
	{
		if (point[i].x - 1 < 0 || !map[point[i].y][point[i].x + 1]
			|| map[point[i].y][point[i].x + 1] == 'X'
			|| map[point[i].y][point[i].x - 1] == 'X' || point[i].y - 1 < 0
			|| !map[point[i].y + 1] || map[point[i].y + 1][point[i].x] == 'X'
			|| map[point[i].y - 1][point[i].x] == 'X')
			return (false);
		i++;
	}
	free(*p);
	*p = NULL;
	return (true);
}

int	load_normal_color(mlx_texture_t *texture, int x, int y)
{
	int		pos;
	uint8_t	*pixel_data;
	t_int	color;
	int		texture_height;
	int		texture_width;

	color = 0;
	texture_height = texture->height;
	texture_width = texture->width;
	pos = (y * texture_width * texture->bytes_per_pixel) + x
		* texture->bytes_per_pixel;
	if (pos < 0 || y < 0 || y >= texture_height || x < 0 || x >= texture_width
		|| pos >= texture_width * texture_height * texture->bytes_per_pixel)
		return (0);
	pixel_data = &(texture->pixels[pos]);
	color = ((pixel_data[0] << 24) | (pixel_data[1] << 16)
			| (pixel_data[2] << 8) | (pixel_data[3]));
	return (color);
}

void	draw_gun(t_player *player, mlx_texture_t *texture)
{
	int			x_c;
	int			y_b;
	int			i;
	int			j;
	uint32_t	color;

	x_c = (WIDTH / 2) - (texture->width);
	y_b = HEIGHT - texture->height * 2;
	i = 0;
	while (i < (int)texture->height * 2)
	{
		j = 0;
		while (j < (int)texture->width * 2)
		{
			color = load_normal_color(texture, j / 2, i / 2);
			if (color != 0)
				mlx_put_pixel(player->img, x_c + j, y_b + i, color);
			j++;
		}
		i++;
	}
}

void	free_textures(t_player *player)
{
	int	i;

	i = 0;
	free_content_tex(player);
	if (!player->gun_texture)
		return ;
	while (i < 11)
	{
		if (player->gun_texture && player->gun_texture[i])
			free(player->gun_texture[i]->pixels);
		free(player->gun_texture[i]);
		i++;
	}
	free(player->gun_texture);
}

bool	valid_door(char **map, t_point *point)
{
	int	i;

	i = 0;
	while (point[i].x != -1 && point[i].y != -1)
	{
		if ((!map[point[i].y][point[i].x + 1]
			|| map[point[i].y][point[i].x + 1] != '1'
			|| point[i].x - 1 < 0 || map[point[i].y][point[i].x - 1] != '1')
			&& (!map[point[i].y + 1] || map[point[i].y + 1][point[i].x] != '1'
			|| point[i].y - 1 < 0 || map[point[i].y - 1][point[i].x] != '1'))
			return (ft_putendl_fd(POS_DOOR, STDERR_FILENO), false);
		i++;
	}
	return (true);
}
