/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:16:17 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/12 12:09:08 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo_bonus.h"

static int	valid_num_check(const char *str, int sign)
{
	long long int	res;

	res = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			return (0);
		str++;
	}
	if (!(*str > '0' && *str <= '9'))
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if ((sign == 1 && res > 2147483647) || (sign == -1 && res > 2147483648))
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
			return(0);
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
		if (!valid_num_check(av[i], 1))
			return (0);
		i++;
	}
	return (1);
}
