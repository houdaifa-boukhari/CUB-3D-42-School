/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:02:55 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/07/30 17:44:49 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	i = 0;
	if (!haystack || !needle)
		return (NULL);
	if (needle[i] == '\0')
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	while (haystack[i] && len > i)
	{
		if (ft_strncmp(haystack + i, needle, needle_len) == 0
			&& len >= (i + needle_len))
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
