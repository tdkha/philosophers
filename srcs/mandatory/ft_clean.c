/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:59:31 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/26 07:41:11 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_mutexes_clean(t_program *prog)
{
	int		i;

	i = 0;
	if (prog->mt_forks)
	{
		while (i < prog->philo_count)
		{
			ft_mutex(&prog->mt_forks[i], DESTROY, prog);
			i++;
		}
		free(prog->mt_forks);
		prog->mt_forks = NULL;
	}
	ft_mutex(&prog->mt_lock_print, DESTROY, prog);
	ft_mutex(&prog->mt_lock_meal, DESTROY, prog);
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

int	ft_philos_clean_destroy(t_program *prog)
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

int	ft_clean(t_program *prog, t_clean_code code)
{
	if (code == ALL)
		ft_free(prog);
	else if (code == PHILO)
	{
		ft_philos_clean(prog);
	}
	else if (code == MUTEX)
	{
		ft_mutexes_clean(prog);
	}
	else
		return (0);
	return (1);
}