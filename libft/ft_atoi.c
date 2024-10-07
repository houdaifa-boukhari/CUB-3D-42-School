/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:11:15 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/10/02 12:57:32 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(long long nb, int n)
{
	if ((nb >= 922337203685477580 && n > 7) || (nb < 0))
		return (1);
	return (0);
}

int	convert(const char *str, int signe)
{
	int				i;
	int				cheack;
	long long		result;

	i = 0;
	result = 0;
	cheack = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		cheack = check(result, str[i] - 48);
		if (cheack == 1)
			result = result * 10 + (str[i] - 48);
		else
			return (cheack);
		i++;
	}
	return ((int)result * signe);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	re;

	i = 0;
	re = 0;
	signe = 1;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		re = re * 10 + (str[i] - '0');
		i++;
	}
	return (re * signe);
}

int	atoi_(char *str)
{
	int			i;
	long long	result;

	i = 0;
	result = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result < 0 || result > 255)
			return (-1);
		i++;
	}
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i])
		return (-1);
	return (result);
}

int	count_arrays(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
