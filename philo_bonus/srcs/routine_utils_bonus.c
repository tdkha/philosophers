/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:59:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/12 23:16:05 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_pick_forks(t_philo *philo)
{
	int	status;

	status = sem_wait(philo->prog->sem_forks);
	if (status != 0)
		return (0);
	status = philo_msg(philo, "has taken a fork");
	if (status == 0)
		return (0);
	status = sem_wait(philo->prog->sem_forks);
	if (status != 0)
		return (0);
	status = philo_msg(philo, "has taken a fork");
	if (status == 0)
		return (0);
	return (1);
}

int	ft_drop_forks(t_philo *philo)
{
	int	status;

	status = sem_post(philo->prog->sem_forks);
	if (status != 0)
		return (
			error_msg_ret("Error: ft_drop_forks from sem_wait()\n", 0));
	status = sem_post(philo->prog->sem_forks);
	if (status != 0)
		return (error_msg_ret("Error: ft_drop_forks from sem_post()\n", 0));
	return (1);
}

int	ft_eat(t_philo *philo)
{
	if (sem_wait(philo->prog->sem_shared) != 0)
		return (error_msg_ret("Error: ft_eat from sem_wait()\n", 0));
	philo->meal_eaten++;
	philo->last_meal_ms = get_current_time();
	if (sem_post(philo->prog->sem_shared) != 0)
		return (error_msg_ret("Error: ft_eat from sem_post()\n", 0));
	if (philo_msg(philo, "is eating") == 0)
		return (0);
	ft_usleep(philo->prog->time_eat);
	if (!ft_drop_forks(philo))
		return (0);
	if (philo->meal_eaten == philo->prog->must_eat)
		sem_post(philo->prog->sem_end);
	return (1);
}

int	ft_sleep_think(t_philo *philo)
{
	int	status;

	status = philo_msg(philo, "is sleeping");
	if (status == 0)
		return (0);
	ft_usleep(philo->prog->time_sleep);
	status = philo_msg(philo, "is thinking");
	if (status == 0)
		return (0);
	return (1);
}
