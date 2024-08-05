/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:17:18 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/05 14:09:14 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

void	error_msg(char *str, t_mutex *mt_lock)
{
	int	len;

	pthread_mutex_lock(mt_lock);
	len = (int) ft_strlen(str);
	(void)!write(2, str, len);
	pthread_mutex_unlock(mt_lock);
}

void	non_blocking_error_msg(char *str)
{
	int	len;

	len = (int) ft_strlen(str);
	(void)!write(2, str, len);
}

int	non_blocking_error_msg_ret(char *str, int val)
{
	int	len;

	len = (int) ft_strlen(str);
	(void)!write(2, str, len);
	return (val);
}

int	error_msg_ret(char *str, t_mutex *mt_lock, int return_val)
{
	int	len;

	pthread_mutex_lock(mt_lock);
	len = (int) ft_strlen(str);
	(void)!write(2, str, len);
	pthread_mutex_unlock(mt_lock);
	return (return_val);
}

int	philo_msg(t_philo *philo, char *str)
{
	size_t	time;

	time = get_current_time(philo->mt_lock) - philo->start_ms;
	pthread_mutex_lock(philo->mt_lock);
	if (*philo->terminate == 1)
		return (pthread_mutex_unlock(philo->mt_lock), 0);
	printf("%zu %d %s\n", time, philo->id + 1, str);
	pthread_mutex_unlock(philo->mt_lock);
	return (1);
}
