/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 00:34:40 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/10/02 19:15:44 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	strlen_(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*strjoin(char *str, char *str1)
{
	char	*new_str;
	int		len;
	int		i;

	i = 0;
	if (!str1)
		return (NULL);
	len = strlen_(str) + strlen_(str1);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (free(str), str = NULL, NULL);
	if (str)
	{
		while (str[i])
		{
			new_str[i] = str[i];
			i++;
		}
		free(str);
		str = NULL;
	}
	while (*str1)
		new_str[i++] = *str1++;
	new_str[i] = '\0';
	return (new_str);
}

char	*update(char *str)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = NULL;
	if (!str)
		return (NULL);
	while (*str && *str != '\n')
		str++;
	str++;
	if (!str || !*str)
		return (NULL);
	i = strlen_(str);
	new_str = malloc(sizeof(char) * (i + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*last_word(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	new_str = (char *)malloc(sizeof(char) * (i + 2));
	if (!new_str)
		return (NULL);
	while (str[j] && j < i)
	{
		new_str[j] = str[j];
		j++;
	}
	new_str[j++] = '\n';
	new_str[j] = '\0';
	free(str);
	str = NULL;
	return (new_str);
}
