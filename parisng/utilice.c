/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:45:08 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/23 16:27:56 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	valide_arg(char *file, int *fd)
{
	char    *str;

	str = ft_strrchr(file, '.');
	if (ft_strcmp(str, ".cub") != 0)
	{
		ft_putendl_fd("Invalide extention use \"file_name.cub\"", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	*fd = open(file, O_RDONLY , 0644);
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
	new_row->row = ft_strtrim(line, "\t \n");
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

void	find_start(t_map *map, char	*line)
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

void	free_inf(t_inf	inf)
{
	free(inf.s_path);
	free(inf.n_path);
	free(inf.w_path);
	free(inf.e_path);
	free(inf.f_color);
	free(inf.c_color);
	free_arrays(inf.inf_map);
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
		return (false);
	}
	free(*path);
	*path = ft_strdup(tmp[1]);
	free_arrays(tmp);
	return (true);
}

void	print_information(t_inf inf)
{
	for (int i = 0; inf.inf_map[i]; i++)
		printf("%s\n", inf.inf_map[i]);
	printf("----------\n");
	printf("E:%s\n", inf.e_path);
	printf("W:%s\n", inf.w_path);
	printf("S:%s\n", inf.s_path);
	printf("N:%s\n", inf.n_path);
	printf("new_color:%d\n", inf.color_f);
	printf("new_color:%d\n", inf.color_c);
}

bool	color_is_valid(char	**color)
{
	int		i;
	int		j;
	bool	check;
	t_color	n_color;

	i = -1;
	check = false;
	while (color[++i])
	{
		j = -1;
		while (color[i][++j])
			if (ft_isdigit(color[i][j]))
				check = true;
		if (!check)
			return (false);
		check = true;
	}
	n_color.r = ft_atoi(color[0]);
	n_color.g = ft_atoi(color[1]);
	n_color.r = ft_atoi(color[2]);
	if (n_color.r > 255 || n_color.r < 0 || n_color.g > 255
		|| n_color.g < 0 || n_color.b > 255 || n_color.b < 0)
		return (false);
	return (true);
}
bool	catch_color(char *p_color, int *n_color)
{
	int		end;
	int 	start;
	char	*color;
	char	**rgb_color;

	start = 0;
	while (p_color[start] && !ft_isdigit(p_color[start]))
		start++;
	end = ft_strlen(p_color) - 1;
	while (p_color[end] && !ft_isdigit(p_color[end]))
		end--;
	color = ft_substr(p_color, start, (end - start + 1));
	if (!color || !*color)
		return (free(color), false);
	rgb_color = ft_split(color, ',');
	if (count_arrays(rgb_color) != 3)
		return(free_arrays(rgb_color), free(color), false);
	if (!color_is_valid(rgb_color))
		return (free_arrays(rgb_color), free(color), false);
	*n_color = (ft_atoi(rgb_color[0]) << 16 | ft_atoi(rgb_color[0]) << 8 | ft_atoi(rgb_color[0]));
	return (free_arrays(rgb_color), free(color), true);
}

bool	check_errors(t_inf inf)
{
	if (!inf.e_path || !inf.w_path || !inf.n_path
		|| !inf.s_path || !inf.f_color || !inf.c_color)
	{
		free_inf(inf);
		ft_putendl_fd("Invalid information", STDERR_FILENO);
		return (false);
	}
	if (!valide_path(&(inf.e_path)) || !valide_path(&(inf.w_path))
		|| !valide_path(&(inf.n_path)) || !valide_path(&(inf.s_path))
		|| !catch_color(inf.c_color, &(inf.color_c)) || !catch_color(inf.f_color, &(inf.color_f)))
	{
		free_inf(inf);
		ft_putendl_fd("format is invalid", STDERR_FILENO);
		return (false);
	}
	print_information(inf);
	return (true);
}
