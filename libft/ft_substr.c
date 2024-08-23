/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:33:21 by hel-bouk          #+#    #+#             */
/*   Updated: 2023/12/07 14:53:32 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	len_s;

	str = NULL;
	i = 0;
	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start > len_s)
	{
		len = 0;
		start = 0;
	}
	else if (start + len > len_s)
		len = len_s - start;
	str = (char *)malloc((sizeof(char) * len) + 1);
	if (!str)
		return (NULL);
	while (s[start] && len > i)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
