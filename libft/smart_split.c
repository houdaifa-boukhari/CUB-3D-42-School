/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:45:05 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/04/16 22:17:51 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define DELIM "\t \n"

int	is_delim(char c)
{
	int	i;

	i = 0;
	while (DELIM[i])
	{
		if (c == DELIM[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_word(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_delim(str[i]))
			i++;
		if (str[i] && !is_delim(str[i]))
			count++;
		while (str[i] && !is_delim(str[i]))
			i++;
	}
	return (count);
}

char	*ft_stardup(char *str, int len)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	**new_split(char *str)
{
	t_va	va;
	char	**new_str;

	va.i = 0;
	va.nb_words = count_word(str);
	va.start = 0;
	new_str = (char **)malloc(sizeof(char *) * (va.nb_words + 1));
	if (!new_str)
		return (NULL);
	while (va.i < va.nb_words)
	{
		while (str[va.start] && is_delim(str[va.start]))
			va.start++;
		va.end = va.start;
		while (str[va.end] && !is_delim(str[va.end]))
			va.end++;
		new_str[va.i] = ft_stardup(str + va.start, va.end - va.start);
		if (!new_str[va.i])
			return (NULL);
		va.start = va.end;
		va.i++;
	}
	new_str[va.i] = NULL;
	return (new_str);
}
