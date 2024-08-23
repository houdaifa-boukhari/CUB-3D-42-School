/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:21:24 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/04/16 18:46:35 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		i;

	if (!s1)
		return (NULL);
	i = ft_strlen((char *)s1) + 1;
	dest = (char *)malloc(sizeof(char) * i);
	if (!dest)
		return (NULL);
	ft_strcpy(dest, s1);
	return (dest);
}
