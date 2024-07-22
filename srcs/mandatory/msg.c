/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:49:06 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/22 23:01:51 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	error_msg(char *str)
{
	int	len;

	len = (int) ft_strlen(str);
	write(2, str, len);
}

int	error_msg_ret(char *str, int return_val)
{
	int	len;

	len = (int) ft_strlen(str);
	write(2, str, len);
	return (return_val);
}

void	philo_msg(t_philo *philo, t_philo_status status)
{
	if (status == FORK)
	{
		printf("%d has taken a fork\n", philo->id);
	}
	else if (status == EAT)
	{
		printf("%d is eating\n", philo->id);
	}
	else if (status == THINK)
	{
		printf("%d is thinking\n", philo->id);
	}
	else if (status == SLEEP)
	{
		printf("%d is sleeping\n", philo->id);
	}
	else if (status == DIE)
	{
		printf("%d died\n", philo->id);
	}
}
