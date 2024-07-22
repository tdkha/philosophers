/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:29:55 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/22 19:00:52 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_mutex(t_mutex *mutex, t_mutex_code code)
{
	int	error;

	error = 0;
	if (code == INIT)
		error = pthread_mutex_init(mutex, NULL);
	else if (code == DESTROY)
		error = pthread_mutex_destroy(mutex);
	else if (code == LOCK)
		error = pthread_mutex_lock(mutex);
	else if (code == UNLOCK)
		error = pthread_mutex_unlock(mutex);
	else
		return (0);
	if (error != 0)
	{
		if (code == INIT)
			error_msg("Error occured when calling <pthread_mutex_init>\n");
		else if (code == DESTROY)
			error_msg("Error occured when calling <pthread_mutex_destroy>\n");
		else if (code == LOCK)
			error_msg("Error occured when calling <pthread_mutex_lock>\n");
		else if (code == UNLOCK)
			error_msg("Error occured when calling <pthread_mutex_unlock>\n");
		return (0);
	}
	return (1);
}

int	ft_mutexes_clean(t_program *prog, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		ft_mutex(&prog->mt_forks[i], DESTROY);
		++i;
	}
	ft_mutex(&prog->mt_lock_print, DESTROY);
	ft_mutex(&prog->mt_lock_meal, DESTROY);
	return (1);
}

int	ft_mutexes_init(t_program *prog)
{
	int	i;

	i = 0;
	if (!ft_mutex(&prog->mt_lock_meal, INIT))
		return (0);
	if (!ft_mutex(&prog->mt_lock_print, INIT))
	{
		ft_mutex(&prog->mt_lock_meal, DESTROY);
		return (0);
	}
	while (i < prog->philo_count)
	{
		if (!ft_mutex(&prog->mt_forks[i], INIT))
		{
			ft_mutexes_clean(prog, i);
			return (error_msg_ret("Failed to init type (t_mutex *)", 0));
		}
		++i;
	}
	return (1);
}
