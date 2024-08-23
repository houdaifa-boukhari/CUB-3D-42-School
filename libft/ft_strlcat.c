/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:46:20 by hel-bouk          #+#    #+#             */
/*   Updated: 2023/12/16 22:34:41 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_lenght;
	size_t	dst_lenght;
	size_t	i;
	size_t	j;

	i = 0;
	src_lenght = ft_strlen(src);
	dst_lenght = ft_strlen((const char *)dst);
	j = dst_lenght;
	if (dst_lenght >= dstsize)
		return (src_lenght + dstsize);
	while (src[i] && (i < (dstsize - dst_lenght - 1)))
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (src_lenght + dst_lenght);
}
