/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:04:47 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/23 14:32:45 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(t_map *map)
{
	while (map)
	{
		printf("%s->%d\n", map->row, map->s_x);
		map = map->next;
	}
}
int main(int ac, char **av)
{
	int fd;
	t_map	*map;
	t_inf	inf;

	map = NULL;
	if (ac == 2)
	{
		initialize_inf(&inf);
		valide_arg(av[1], &fd);
		take_map(&map, fd);
		// print_map(map);
		take_information(map, &inf);
		parsing_information(&inf);
		if (!check_errors(inf))
			exit(EXIT_FAILURE);
		// free_map(&map);
	}
	else
		ft_putendl_fd("Use ./cub3D file.cub", STDERR_FILENO);
	return (0);
}