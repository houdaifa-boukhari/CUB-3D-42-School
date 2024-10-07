/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:29:06 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/10/02 12:32:31 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	check_map_err(t_map *map)
{
	int		i;
	bool	check;
	t_map	*ptr;

	i = 0;
	check = true;
	if (!map)
		return (false);
	ptr = get_position(map, 7);
	while (ptr)
	{
		if (!ptr->row[0])
			check = false;
		else if (ptr->row && !check)
			return (ft_putendl_fd(MAP_V, STDERR_FILENO), false);
		ptr = ptr->next;
	}
	return (true);
}

void	back_to_default(char **map, char c)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'F' || map[i][j] == 'X' || map[i][j] == c)
				map[i][j] = '0';
			j++;
		}
		i++;
	}
}

int	count_charcter(char **str, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == c)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

t_point	*get_position_door(char **map)
{
	int		i;
	int		j;
	int		k;
	t_point	*point;

	k = 0;
	point = (t_point *)malloc(sizeof(t_point) * (count_charcter(map, 'D') + 1));
	if (!point)
		return (NULL);
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'D')
			{
				point[k].x = j;
				point[k++].y = i;
			}
		}
	}
	point[k].x = -1;
	point[k].y = -1;
	return (point);
}

t_int	load_colors(t_player *player, mlx_texture_t *texture, 
			t_fpoint x, t_arg_w args)
{
	double	tmp;
	t_int	pos;
	t_point	p_tex;
	uint8_t	*pixel_data;

	if (!player->is_vertical)
		p_tex.x = ((x.x / PEX) - floor(x.x / PEX)) * texture->width;
	else
		p_tex.x = ((x.y / PEX) - floor(x.y / PEX)) * texture->width;
	if (args.check)
		player->texture_offset = args.tmp * texture->height;
	tmp = (int)(player->pos_y - player->wall_t) * texture->height;
	p_tex.y = tmp / player->wall_height + player->texture_offset;
	pos = ((int)p_tex.y * texture->width * texture->bytes_per_pixel)
		+ (int)p_tex.x * texture->bytes_per_pixel;
	if (pos < 0 || p_tex.y < 0 || (uint32_t)p_tex.y >= texture->height
		|| p_tex.x < 0 || (uint32_t)p_tex.x >= texture->width
		|| pos >= (texture->width * texture->height * texture->bytes_per_pixel))
		return (0);
	pixel_data = &(texture->pixels[pos]);
	if (!pixel_data)
		return (0);
	return ((pixel_data[0] << 24) | (pixel_data[1] << 16)
		| (pixel_data[2] << 8) | (pixel_data[3]));
}
