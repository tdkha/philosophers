/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:49:06 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/31 12:43:50 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	error_msg(t_program *prog, char *str)
{
	int	len;

	ft_mutex(&prog->mt_lock_print, LOCK, prog);
	len = (int) ft_strlen(str);
	ft_mutex(&prog->mt_lock_print, UNLOCK, prog);
	write(2, str, len);
}

int	error_msg_ret(t_program *prog, char *str, int return_val)
{
	int	len;

	ft_mutex(&prog->mt_lock_print, LOCK, prog);
	len = (int) ft_strlen(str);
	write(2, str, len);
	ft_mutex(&prog->mt_lock_print, UNLOCK, prog);
	return (return_val);
}

static int	dead_not_print(t_philo *philo, size_t time)
{
	ft_mutex(&philo->prog->mt_lock_meal, LOCK, philo->prog);
	if (time >= (size_t)philo->prog->time_die && philo->eating == 0)
	{
		ft_mutex(&philo->prog->mt_lock_meal, UNLOCK, philo->prog);
		return (1);
	}
	ft_mutex(&philo->prog->mt_lock_meal, UNLOCK, philo->prog);
	return (0);
}

void	philo_msg(t_philo *philo, t_philo_status status)
{
	size_t	time;

	time = get_current_time(philo->prog) - philo->start_ms;
	ft_mutex(&philo->prog->mt_lock_print, LOCK, philo->prog);
	if (status == DIE)
	{
		printf("%zu %d died\n", time, philo->id);
		ft_mutex(&philo->prog->mt_lock_print, UNLOCK, philo->prog);
		return ;
	}
	if (dead_not_print(philo, time))
		return ;
	if (status == FORK_UP_L || status == FORK_UP_R)
		printf("%zu %d has taken a fork\n", time, philo->id);
	else if (status == FORK_DOWN_L || status == FORK_DOWN_R)
		printf("%zu %d has released a fork\n", time, philo->id);
	else if (status == EAT)
		printf("%zu %d is eating\n", time, philo->id);
	else if (status == THINK)
		printf("%zu %d is thinking\n", time, philo->id);
	else if (status == SLEEP)
		printf("%zu %d is sleeping\n", time, philo->id);
	ft_mutex(&philo->prog->mt_lock_print, UNLOCK, philo->prog);
}
