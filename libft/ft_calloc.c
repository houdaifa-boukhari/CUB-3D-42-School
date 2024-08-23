/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:39:21 by hel-bouk          #+#    #+#             */
/*   Updated: 2023/12/19 09:08:07 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*memory;
	size_t	check_over;

	check_over = count * size;
	if (count != 0 && size != (check_over / count))
		return (NULL);
	memory = malloc(count * size);
	if (!memory)
		return (NULL);
	ft_memset(memory, 0, count * size);
	return (memory);
}
