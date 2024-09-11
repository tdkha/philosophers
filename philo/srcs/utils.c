/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:22:53 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/11 17:22:18 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->mt_terminate);
	if (philo->terminate && *philo->terminate == 1)
	{
		pthread_mutex_unlock(philo->mt_terminate);
		return (1);
	}
	pthread_mutex_unlock(philo->mt_terminate);
	return (0);
}

void	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		if (philo)
		{
			if (check_dead(philo))
				return ;
		}
		usleep(1000);
	}
}

void	print_end(t_program *prog, t_philo *philo)
{
	pthread_mutex_lock(&prog->mt_print);
	if (prog->must_eat != -1
		&& prog->philo_full_count == prog->philo_count)
		printf("Every philosopher ate %d times\n", prog->must_eat);
	else
		printf("%zu %d died\n",
			get_current_time() - philo->start_ms, philo->id + 1);
	pthread_mutex_unlock(&prog->mt_print);
}
