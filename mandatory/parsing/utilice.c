/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:45:08 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/10/06 15:08:38 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	valide_arg(char *file, int *fd)
{
	char	*str;

	str = ft_strrchr(file, '.');
	if (ft_strcmp(str, ".cub") != 0)
	{
		ft_putendl_fd("Invalide extention use \"file_name.cub\"",
			STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	*fd = open(file, O_RDONLY, 0644);
	if (*fd < 0)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}
}

void	creat_list(t_map **map, char *line)
{
	t_map	*ptr;
	t_map	*new_row;

	if (!map)
		return ;
	new_row = (t_map *)malloc(sizeof(t_map));
	if (!new_row)
		return ;
	new_row->row = ft_strtrim(line, " \n");
	new_row->next = NULL;
	if (!*map)
	{
		*map = new_row;
		(*map)->prev = NULL;
		return ;
	}
	ptr = *map;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new_row;
	new_row->prev = ptr;
}

void	find_start(t_map *map, char *line)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map->next)
		map = map->next;
	while (line[i] && is_space(line[i]))
		i++;
	map->s_x = i;
}

void	free_inf(t_inf *inf)
{
	free(inf->s_path);
	free(inf->n_path);
	free(inf->w_path);
	free(inf->e_path);
	free(inf->f_color);
	free(inf->c_color);
	free_arrays(inf->inf_map);
	initialize_inf(inf);
}

bool	valide_path(char **path)
{
	int		count;
	char	**tmp;

	tmp = new_split(*path);
	count = count_arrays(tmp);
	if (count != 2)
	{
		ft_putendl_fd("Invalid format", STDERR_FILENO);
		return (free_arrays(tmp), false);
	}
	free(*path);
	*path = ft_strdup(tmp[1]);
	free_arrays(tmp);
	return (true);
}
