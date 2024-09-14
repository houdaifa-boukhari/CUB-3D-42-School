/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:04:47 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/09/14 10:56:17 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(char **map)
{
	printf("---------\n");
	for(int i = 0; map[i]; i++)
		printf("%s\n", map[i]);
}

void	print_information(t_inf inf)
{
	printf("SO:%s\n", inf.s_path);
	printf("NO:%s\n", inf.n_path);
	printf("WE:%s\n", inf.w_path);
	printf("EA:%s\n", inf.e_path);
	printf("flow color:%d\n", inf.color_f);
	printf("celeng color:%d\n", inf.color_c);
}

void	assign_player(t_player *player, char **map, t_inf inf)
{
	t_point	p;

	p = find_empty_space(map, inf.position);
	player->x = p.x;
	player->y = p.y;
	player->color_sky = inf.color_c;
	player->color_floor = inf.color_f;
	player->map = map;
	if (inf.position == 'N')
		player->angle = (PI / 2.0);
	else if (inf.position == 'S')
		player->angle = (-PI / 2.0);
	else if (inf.position == 'E')
		player->angle = (PI);
	else if (inf.position == 'W')
		player->angle = (0);
}

void init_all_data(char **av, t_player *player)
{
	int		fd;
	t_inf	inf;
	t_map	*map;
	char	**map_2d;

	map = NULL;
	initialize_inf(&inf);
	valide_arg(av[1], &fd);  
	take_map(&map, fd);
	take_information(map, &inf);
	parsing_information(&inf);
	if (!check_errors(&inf) || !valid_ch(map, &inf) || !check_map_err(map))
		return (free_inf(&inf), free_map(&map), exit(EXIT_FAILURE));
	print_information(inf);
	check_map_err(map);
	map_2d = built2darray(map);
	assign_player(player, map_2d, inf);
	if (!map_isclosed(map_2d, inf.position))
		return (print_map(map_2d), free_inf(&inf), free_map(&map), free_arrays(map_2d), exit(EXIT_FAILURE));
	back_to_default(map_2d);
	print_map(map_2d);
	free_inf(&inf);
	free_map(&map);
	// free_arrays(map_2d);
}

int main(int ac, char **av)
{
	t_player	player;

	if (ac == 2)
	{
		init_all_data(av, &player);
	}
	else
		ft_putendl_fd("Use ./cub3D file.cub", STDERR_FILENO);
	
}
