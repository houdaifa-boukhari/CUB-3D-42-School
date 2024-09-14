/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:52:22 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/29 18:12:03 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_errors(t_inf *inf)
{
	if (!inf->e_path || !inf->w_path || !inf->n_path
		|| !inf->s_path || !inf->f_color || !inf->c_color)
	{
		free_inf(inf);
		ft_putendl_fd("Invalid information", STDERR_FILENO);
		return (false);
	}
	if (!valide_path(&(inf->e_path)) || !valide_path(&(inf->w_path))
		|| !valide_path(&(inf->n_path)) || !valide_path(&(inf->s_path))
		|| !catch_color(inf->c_color, &(inf->color_c)) || !catch_color(inf->f_color, &(inf->color_f)))
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
	map = get_position(map, 7);
	if (!map)
		return (ft_putendl_fd(NOT_EXIST, STDERR_FILENO), false);
	while (map)
	{
		i = 0;
		while (map->row[i])
		{
			if ((check_ch(map->row[i], P_PLAYER) && check) || !check_ch(map->row[i], V_CH))
				return (ft_putendl_fd(ERR_CH, STDERR_FILENO), false);
			if (check_ch(map->row[i], P_PLAYER))
			{
				inf->position = map->row[i];
				check = true;
			}
			i++;
		}
		map = map->next;
	}
	if (!inf->position)
		return (ft_putendl_fd(PY_ERR, STDERR_FILENO), false);
	return (true);
}

bool	map_isclosed(char **map, char c)
{
	bool	check;
	t_point x;

	x = find_empty_space(map, '0');
	while (x.x != -1 && x.y != -1)
	{
		check = flood_fill(map, x);
		if (!check)
			return (false);
		x = find_empty_space(map, '0');
	}
	x = find_empty_space(map, c);
	if (x.x != -1 && x.y != -1)
		check = flood_fill(map, x);
	return (check);
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

