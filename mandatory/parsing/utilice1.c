/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilice1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 09:28:08 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/09/16 19:57:08 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_map(t_map **map)
{
	t_map	*current;
	t_map	*next;

	if (!map || !*map)
		return ;
	current = *map;
	while (current)
	{
		next = current->next;
		free(current->row);
		free(current);
		current = next;
	}
	*map = NULL;
	map = NULL;
}

int	count_exist_line(t_map *map)
{
	int	i;

	i = 0;
	while (map)
	{
		if (map->row[0])
			i++;
		map = map->next;
	}
	return (i);
}

t_map	*get_position(t_map *map, int idx)
{
	int	i;

	i = 0;
	while (map && i <= idx)
	{
		if (map->row[0])
			i++;
		if (i == idx)
			return (map);
		map = map->next;
	}
	return (map);
}

char	**built2darray(t_map *map)
{
	int		i;
	int		count;
	int		max;
	t_map	*ptr;
	char	**map_2d;

	i = 0;
	if (!map)
		return (NULL);
	ptr = get_position(map, 7);
	max = get_max(ptr);
	count = count_exist_line(ptr);
	map_2d = (char **)malloc(sizeof(char *) * (count + 1));
	if (!map_2d)
		return (NULL);
	while (i < count && ptr)
	{
		if (ptr->row[0])
			map_2d[i++] = fill_spaces(ptr->row, ptr->s_x, max);
		ptr = ptr->next;
	}
	map_2d[i] = NULL;
	return (map_2d);
}
