/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_err_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:52:22 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/10/06 15:09:15 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

bool	check_errors(t_inf *inf)
{
	if (!inf->e_path || !inf->w_path || !inf->n_path || !inf->s_path
		|| !inf->f_color || !inf->c_color)
	{
		free_inf(inf);
		ft_putendl_fd("Invalid information", STDERR_FILENO);
		return (false);
	}
	if (!valide_path(&(inf->e_path)) || !valide_path(&(inf->w_path))
		|| !valide_path(&(inf->n_path)) || !valide_path(&(inf->s_path))
		|| !catch_color(inf->c_color, &(inf->color_c))
		|| !catch_color(inf->f_color, &(inf->color_f)))
	{
		free_inf(inf);
		ft_putendl_fd("format is invalid", STDERR_FILENO);
		return (false);
	}
	return (true);
}

bool	valid_ch(t_map *map, t_inf *inf)
{
	int		i;
	bool	check;

	check = false;
	if (!map)
		return (ft_putendl_fd(NOT_EXIST, STDERR_FILENO), false);
	while (map)
	{
		i = -1;
		while (map->row[++i])
		{
			if ((check_ch(map->row[i], P_PLAYER) && check)
				|| !check_ch(map->row[i], V_CH))
				return (ft_putendl_fd(ERR_CH, STDERR_FILENO), false);
			if (check_ch(map->row[i], P_PLAYER))
			{
				inf->position = map->row[i];
				check = true;
			}
		}
		map = map->next;
	}
	if (!inf->position)
		return (ft_putendl_fd(PY_ERR, STDERR_FILENO), false);
	return (true);
}

bool	map_isclosed(char **map, char c, t_point **point)
{
	int		i;
	t_point	x;
	bool	check;

	i = 0;
	x = find_empty_space(map, '0');
	while (x.x != -1 && x.y != -1)
	{
		check = flood_fill(map, x);
		if (!check)
			return (false);
		x = find_empty_space(map, '0');
	}
	x = find_empty_space(map, c);
	if (x.x - 1 < 0 || !map[x.y][x.x + 1] || map[x.y][x.x + 1] == 'X'
		|| map[x.y][x.x - 1] == 'X' || x.y - 1 < 0 || !map[x.y + 1]
			|| map[x.y + 1][x.x] == 'X' || map[x.y - 1][x.x] == 'X')
		return (ft_putendl_fd(MAP_ERR, STDERR_FILENO), false);
	if (!door_is_s(point, map))
		return (ft_putendl_fd(POS_DOOR, STDERR_FILENO), false);
	return (true);
}

bool	check_wall(char **map, t_point begin, t_point size)
{
	if (map[begin.y][begin.x] != '1')
	{
		if (((begin.x + 1) < size.x) && map[begin.y][begin.x + 1] == 'X')
			return (false);
		else if (((begin.y + 1) < size.y) && map[begin.y + 1][begin.x] == 'X')
			return (false);
		else if (((begin.x - 1) > 0) && map[begin.y][begin.x - 1] == 'X')
			return (false);
		else if (((begin.y - 1) > 0) && map[begin.y - 1][begin.x] == 'X')
			return (false);
	}
	return (true);
}
