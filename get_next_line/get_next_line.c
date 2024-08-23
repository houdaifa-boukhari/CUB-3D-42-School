/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 00:39:56 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/10 12:00:59 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_str(char **temp)
{
	char	*str;
	char	*var;

	str = NULL;
	str = last_word(ft_strdup(*temp));
	var = *temp;
	*temp = update(var);
	free(var);
	var = NULL;
	return (str);
}

char	*update_str(char *str, char *buffer)
{
	char	*last;

	last = last_word(ft_strdup(buffer));
	str = strjoin(str, last);
	free(last);
	last = NULL;
	return (str);
}

char	*read_management(int fd, char **temp, char *buffer)
{
	int		byt_read;
	char	*str;

	str = NULL;
	if (*temp && check_line(*temp))
		return (get_str(temp));
	else if (*temp)
		str = *temp;
	*temp = NULL;
	byt_read = read(fd, buffer, BUFFER_SIZE);
	while (byt_read > 0)
	{
		buffer[byt_read] = '\0';
		if (!check_line(buffer))
			str = strjoin(str, buffer);
		else
		{
			str = update_str(str, buffer);
			*temp = update(buffer);
			break ;
		}
		byt_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*buffer;
	char		*line;

	if (read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0 || fd < 0)
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = read_management(fd, &temp, buffer);
	free(buffer);
	buffer = NULL;
	return (line);
}
