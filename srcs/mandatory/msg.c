/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:49:06 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/02 13:16:11 by ktieu            ###   ########.fr       */
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

static int	dead_not_print(t_philo *philo, size_t time) {
	pthread_mutex_lock(philo->mt_lock_dead);
	if (time >= (size_t)philo->time_die && philo->eating == 0) {
		pthread_mutex_unlock(philo->mt_lock_dead);
		return (1);
	}
	pthread_mutex_unlock(philo->mt_lock_dead);
	return (0);
}

void	philo_msg(t_philo *philo, t_philo_status status) {
	size_t	time;

	time = get_current_time(philo->mt_lock_print) - philo->start_ms;
	if (status == DIE) {
		pthread_mutex_lock(philo->mt_lock_print);
		printf("%zu %d died\n", time, philo->id + 1);
		pthread_mutex_unlock(philo->mt_lock_print);
		return ;
	}
	if (dead_not_print(philo, time))
		return ;
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
}