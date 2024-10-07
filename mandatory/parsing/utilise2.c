/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:59:24 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/09/30 14:01:51 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	fill(char **tab, t_point size, t_point begin, char old)
{
	char	new;

	new = 'F';
	if (begin.x >= size.x || begin.y >= size.y || begin.x < 0 || begin.y < 0)
	{
		ft_putendl_fd(MAP_ERR, STDERR_FILENO);
		return (false);
	}
	if (!check_wall(tab, begin, size))
	{
		ft_putendl_fd(MAP_ERR, STDERR_FILENO);
		return (false);
	}
	if (tab[begin.y][begin.x] == old)
		tab[begin.y][begin.x] = new;
	else
		return (true);
	if (!fill(tab, size, (t_point){begin.x + 1, begin.y}, old)
		|| !fill(tab, size, (t_point){begin.x - 1, begin.y}, old)
		|| !fill(tab, size, (t_point){begin.x, begin.y + 1}, old)
		|| !fill(tab, size, (t_point){begin.x, begin.y - 1}, old))
		return (false);
	return (true);
}

bool	flood_fill(char **tab, t_point begin)
{
	bool	check;

	if (!tab || !tab[0])
		return (false);
	check = fill(tab, (t_point){ft_strlen(tab[0]), count_arrays(tab)}, begin,
			tab[begin.y][begin.x]);
	return (check);
}

char	*fill_spaces(char *str, int len, int max)
{
	int		i;
	int		j;
	int		size;
	char	*new_str;

	i = 0;
	size = ft_strlen(str);
	new_str = (char *)malloc(sizeof(char *) * (max + 1));
	if (!new_str)
		return (NULL);
	while (i < len)
		new_str[i++] = 'X';
	j = 0;
	while (i < max)
	{
		if (j < size && str[j] == ' ')
			new_str[i++] = 'X';
		else if (j < size && str[j])
			new_str[i++] = str[j];
		else
			new_str[i++] = 'X';
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}

int	get_max(t_map *map)
{
	int	max;

	if (!map)
		return (0);
	max = map->s_x + (int)ft_strlen(map->row);
	map = map->next;
	while (map)
	{
		if (map->row[0] && ((map->s_x + (int)ft_strlen(map->row)) > max))
			max = map->s_x + ft_strlen(map->row);
		map = map->next;
	}
	return (max);
}

t_point	find_empty_space(char **map, char c)
{
	int		i;
	int		j;
	t_point	cord;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
			{
				cord.x = j;
				cord.y = i;
				return (cord);
			}
			j++;
		}
		i++;
	}
	return ((t_point){-1, -1});
}
