/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:56:32 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/09 12:59:42 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_atold(const char *str)
{
	long long int	res;
	int				sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		if (res > LONG_MAX / 10
			|| (res == LONG_MAX / 10 && (sign * (*str - 48) > (LONG_MAX % 10))))
			return (-1);
		if (res == LONG_MAX / 10 && (sign * (*str - 48) < (LONG_MIN % 10)))
			return (0);
		res = res * 10 + (*str - 48);
		str++;
	}
	return (res * sign);
}


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
	{
		return (1);
	}
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	size_t	total;

	total = count * size;
	if (count > 0 && size > 0 && count != (total / size))
		return (NULL);
	res = malloc(count * size);
	if (!res)
		return (0);
	memset(res, 0, count);
	return (res);
}