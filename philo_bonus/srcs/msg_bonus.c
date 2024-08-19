/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:17:18 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/19 17:55:26 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	error_msg(char *str)
{
	int	len;

	len = (int) ft_strlen(str);
	(void)!write(2, str, len);
}

int	error_msg_ret(char *str, int val)
{
	int	len;

	len = (int) ft_strlen(str);
	(void)!write(2, str, len);
	return (val);
}

int	philo_msg(t_philo *philo, char *str)
{
	size_t	time;

	time = get_current_time() - philo->start_ms;
	if (ft_check_terminate(philo))
		return (1);
	if (sem_wait(philo->prog->sem_print) != 0)
	{
		error_msg("philo_bonus: philo_msg: sem_wait()\n");
		return (0);
	}
	printf("%zu %d %s\n", time, philo->id + 1, str);
	if (sem_post(philo->prog->sem_print) != 0)
	{
		error_msg("philo_bonus: philo_msg: sem_post()\n");
		return (0);
	}
	return (1);
}
