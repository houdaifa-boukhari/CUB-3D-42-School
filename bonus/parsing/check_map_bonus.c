/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:44:49 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/10/02 18:31:26 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	take_map(t_map **map, int fd)
{
	char	*line;

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

void	take_information(t_map *map, t_inf *inf)
{
	int	i;

	i = count_exist_line(map);
	if (i < 6)
		return (inf->inf_map = NULL, free(NULL));
	i = 0;
	inf->inf_map = (char **)malloc(sizeof(char *) * (7));
	if (!inf->inf_map)
		return ;
	while (i < 6 && map)
	{
		if (map->row && *(map->row) != '\0')
			inf->inf_map[i++] = ft_strdup(map->row);
		map = map->next;
	}
	inf->inf_map[i] = NULL;
}

void	parsing_information(t_inf *inf)
{
	int	i;

	i = 0;
	if (!inf->inf_map)
		return ;
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

bool	color_is_valid(char **color, int **color_)
{
	int		i;
	int		j;
	t_color	n_color;

	i = -1;
	while (color[++i])
	{
		j = -1;
		while (color[i][++j])
		{
			if (ft_isdigit(color[i][j]) == 0 && !is_space(color[i][j]))
				return (false);
		}
	}
	n_color.r = atoi_(color[0]);
	n_color.g = atoi_(color[1]);
	n_color.b = atoi_(color[2]);
	if (n_color.r > 255 || n_color.r < 0 || n_color.g > 255 || n_color.g < 0
		|| n_color.b > 255 || n_color.b < 0)
		return (false);
	**color_ = (n_color.r << 24 | n_color.g << 16 | n_color.b << 8 | 255);
	return (true);
}

bool	catch_color(char *p_color, int *n_color)
{
	int		end;
	int		start;
	char	*color;
	char	**rgb_color;

	start = 1;
	while (p_color[start] && is_space(p_color[start]))
		start++;
	end = ft_strlen(p_color) - 1;
	color = ft_substr(p_color, start, (end - start + 1));
	if (!color || !*color || count_ch(color, ',') != 2)
		return (free(color), false);
	rgb_color = ft_split(color, ',');
	if (count_arrays(rgb_color) != 3)
		return (free_arrays(rgb_color), free(color), false);
	if (!color_is_valid(rgb_color, &n_color))
		return (free_arrays(rgb_color), free(color), false);
	return (free_arrays(rgb_color), free(color), true);
}
