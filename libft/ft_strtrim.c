/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:49:03 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/25 09:51:50 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	check_ch(char c, char *delim)
{
	while (*delim)
	{
		if (*delim == c)
			return (true);
		delim++;
	}
	return (false);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*new_str;

	start = 0;
	if (!s1)
		return (NULL);
	else if (!set && s1)
		return ((char *)s1);
	end = ft_strlen(s1);
	while (s1[start] && check_ch(s1[start], (char *)set))
		start++;
	while (check_ch(s1[end - 1], (char *)set) && end > start)
		end--;
	new_str = ft_substr(s1, start, end - start);
	if (!new_str)
		return (NULL);
	return (new_str);
}
