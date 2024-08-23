/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:44:49 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/23 14:50:52 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    take_map(t_map **map, int fd)
{
	char    *line;

	line = get_next_line(fd);
	while (line)
	{
		creat_list(map, line);
		find_start(*map, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void    take_information(t_map *map, t_inf *inf)
{
	int i;
	
	i = 0;
	inf->inf_map = (char **)malloc(sizeof(char *) * (7));
	if (!inf->inf_map)
		return ;
	while (i < 6)
	{
		if (map->row && *(map->row) != '\0')
			inf->inf_map[i++] = ft_strdup(map->row);
		map = map->next;
	}
	inf->inf_map[i] = NULL;
}

void	parsing_information(t_inf *inf)
{
	int		i;

	i = 0;
	while (inf->inf_map[i])
	{
		if (ft_strncmp(inf->inf_map[i], "NO ", 3) == 0)
			inf->n_path = ft_strdup(inf->inf_map[i]);
		else if (ft_strncmp(inf->inf_map[i], "SO ", 3) == 0)
			inf->s_path = ft_strdup(inf->inf_map[i]);
		else if (ft_strncmp(inf->inf_map[i], "WE ", 3) == 0)
			inf->w_path = ft_strdup(inf->inf_map[i]);
		else if (ft_strncmp(inf->inf_map[i], "EA ", 3) == 0)
			inf->e_path = ft_strdup(inf->inf_map[i]);
		else if (ft_strncmp(inf->inf_map[i], "C ", 2) == 0)
			inf->c_color = ft_strdup(inf->inf_map[i]);
		else if (ft_strncmp(inf->inf_map[i], "F ", 2) == 0)
			inf->f_color = ft_strdup(inf->inf_map[i]);
		i++;
	}
}
