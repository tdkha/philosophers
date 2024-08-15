/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:23:47 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/15 15:59:55 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"


int	ft_sem_clean(t_program *prog)
{
	sem_close(prog->sem_forks);
	sem_close(prog->sem_shared);
	sem_close(prog->sem_activate);
	sem_close(prog->sem_print);
	sem_unlink("forks");
	sem_unlink("shared");
	sem_unlink("activate");
	sem_unlink("print");
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
 * - Do not handle the failure of sem function here
 */
int	ft_free(t_program *prog)
{
	if (sem_post(prog->sem_print) != 0)
	{
		error_msg("philo_bonus: end_process: sem_post\n");
	}
	ft_sem_clean(prog);
	ft_philos_clean(prog);
	free(prog);
	return (1);
}
