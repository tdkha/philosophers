/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:49:06 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/03 16:11:53 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	error_msg(char *str, t_mutex *mt_lock_print)
{
	int	len;

	pthread_mutex_lock(mt_lock_print);
	len = (int) ft_strlen(str);
	(void)!write(2, str, len);
	pthread_mutex_unlock(mt_lock_print);
}

int	error_msg_ret(char *str, t_mutex *mt_lock_print, int return_val)
{
	int	len;

	pthread_mutex_lock(mt_lock_print);
	len = (int) ft_strlen(str);
	(void)!write(2, str, len);
	pthread_mutex_unlock(mt_lock_print);
	return (return_val);
}



int	philo_msg(t_philo *philo, t_philo_action status)
{
	size_t	time;

	time = get_current_time(philo->mt_lock_print) - philo->start_ms;
	if (check_dead(philo) == 1)
		return (0);
	pthread_mutex_lock(philo->mt_lock_print);
	if (status == FORK_UP_L || status == FORK_UP_R)
		printf("%zu %d has taken a fork\n", time, philo->id + 1);
	else if (status == EAT)
		printf("%zu %d is eating\n", time, philo->id + 1);
	else if (status == THINK)
		printf("%zu %d is thinking\n", time, philo->id + 1);
	else if (status == SLEEP)
		printf("%zu %d is sleeping\n", time, philo->id + 1);
	pthread_mutex_unlock(philo->mt_lock_print);
	return (1);
}
