/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:23:47 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/13 18:07:40 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	ft_sem_unlink(void)
{
	int	status;

	status = sem_unlink("forks");
	if (status != 0)
		return (0);
	status = sem_unlink("shared");
	if (status != 0)
		return (0);
	status = sem_unlink("activate");
	if (status != 0)
		return (0);
	status = sem_unlink("print");
	if (status != 0)
		return (0);
	status = sem_unlink("end");
	if (status != 0)
		return (0);
	return (1);
}

static int	ft_sem_destroy(t_program *prog)
{
	int	status;

	status = sem_close(prog->sem_forks);
	if (status != 0)
	{
		return (0);
	}
	status = sem_close(prog->sem_shared);
	if (status != 0)
		return (0);
	status = sem_close(prog->sem_activate);
	if (status != 0)
		return (0);
	status = sem_close(prog->sem_print);
	if (status != 0)
		return (0);
	status = sem_close(prog->sem_end);
	if (status != 0)
		return (0);
	return (1);
}

int	ft_philos_clean(t_program *prog)
{
	int	i;

	i = 0;
	if (prog->philos)
	{
		while (i < prog->philo_count)
		{
			if (!prog->philos[i])
				break ;
			free(prog->philos[i]);
			prog->philos[i] = NULL;
			i++;
		}
		free(prog->philos);
		prog->philos = NULL;
	}
	return (1);
}

/**
 * Description:
 * - sem_post in case the philosopher dies (lock until here)
 */
int	ft_free(t_program *prog)
{
	if (sem_post(prog->sem_print) != 0)
	{
		error_msg("philo_bonus: end_process: sem_post\n");
	}
	if (ft_sem_destroy(prog) == 0)
		return (
			error_msg_ret(
				"philo_bonus: ft_sem_destroy: sem_close()\n", 0));
	if (ft_sem_unlink() == 0)
		return (
			error_msg_ret(
				"philo_bonus: ft_sem_unlink: sem_unlink()\n", 0));
	ft_philos_clean(prog);
	free(prog);
	return (1);
}
