/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:49:06 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/09 15:02:13 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	error_msg(char *str, t_mutex *mt_lock)
{
	int	len;

	pthread_mutex_lock(mt_lock);
	len = (int) ft_strlen(str);
	(void)!write(2, str, len);
	pthread_mutex_unlock(mt_lock);
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

/**
 * Function to print out an action of a philosopher
 * 
 * Description: 
 * 
 * - The function first checks for the death of a philosopher before
 * deciding to print or not.
 * - The return of this function should checked
 * 
 */
int	philo_msg(t_philo *philo, char *str)
{
	size_t	time;

	if(check_dead(philo))
	{
		return (0);
	}
	time = get_current_time(philo->mt_lock) - philo->start_ms;
	pthread_mutex_lock(philo->mt_print);
	if (*philo->terminate == 1)
		return (pthread_mutex_unlock(philo->mt_print), 0);
	printf("%zu %d %s\n", time, philo->id + 1, str);
	pthread_mutex_unlock(philo->mt_print);
	return (1);
}

