/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:44:26 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/04/16 21:28:24 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] != c && str[i])
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static void	*free_array(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	else
	{
		while (str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
		free(str);
		str = NULL;
	}
	return (NULL);
}

static char	**allocate_split(char **str, char const *s, char c, int nb_word)
{
	int	start;
	int	len;
	int	i;

	start = 0;
	len = 0;
	i = 0;
	while (i < nb_word)
	{
		while (s[start] && s[start] == c)
			start++;
		len = start;
		while (s[len] && s[len] != c)
			len++;
		str[i] = ft_substr(s, start, len - start);
		if (!str[i])
			return (free_array(str));
		start = len;
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		nb_words;

	if (!s)
		return (NULL);
	nb_words = count_word(s, c);
	str = (char **)malloc(sizeof(char *) * (nb_words + 1));
	if (!str)
		return (NULL);
	if (!allocate_split(str, s, c, nb_words))
		return (NULL);
	return (str);
}
