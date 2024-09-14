/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:29:06 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/09/14 10:52:41 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void back_to_default(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'F' || map[i][j] == 'X')
				map[i][j] = '0';
			j++;
		}
		i++;
	}
}
