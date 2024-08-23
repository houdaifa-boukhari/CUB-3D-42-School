/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:41:28 by hel-bouk          #+#    #+#             */
/*   Updated: 2023/12/15 17:30:13 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(long nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		i++;
	}
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	char	*str_nb;

	nb = (long)n;
	len = count_len(nb);
	str_nb = (char *)malloc(sizeof(char) * (len + 1));
	if (!str_nb)
		return (NULL);
	str_nb[len--] = '\0';
	if (nb == 0)
		str_nb[0] = 48;
	if (nb < 0)
	{
		str_nb[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		str_nb[len] = (nb % 10) + 48;
		nb /= 10;
		len--;
	}
	return (str_nb);
}
