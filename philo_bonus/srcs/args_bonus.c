/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:16:49 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/12 23:58:56 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	valid_int_check(const char *str, int sign)
{
	long long int	res;

	res = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+')
	{
		str++;
	}
	if (*str == '-')
		return (0);
	if (!(*str > '0' && *str <= '9'))
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if ((sign == 1 && res > INT_MAX) || (sign == -1 && res > INT_MIN))
			return (0);
		str++;
	}
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str != '\0')
		return (0);
	return (1);
}

static int	valid_ulong_check(const char *str, int sign)
{
	long long int	res;

	res = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+')
	{
		str++;
	}
	if (*str == '-')
		return (0);
	if (!(*str > '0' && *str <= '9'))
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if ((sign == 1 && (unsigned long)res > ULONG_MAX))
			return (0);
		str++;
	}
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str != '\0')
		return (0);
	return (1);
}

static inline int	generic_check(
	char *str,
	int i)
{
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	if (!str[i] || !ft_isdigit(str[i]))
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	ft_arg_check(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 2)
		return (0);
	while (i < ac)
	{
		if (!generic_check(av[i], 0))
			return (0);
		if (i == 1 || i == ac - 1)
		{
			if (!valid_int_check(av[i], 1))
				return (0);
		}
		else
		{
			if (!valid_ulong_check(av[i], 1))
				return (0);
		}
		i++;
	}
	return (1);
}
