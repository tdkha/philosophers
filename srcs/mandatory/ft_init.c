/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:08:25 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/02 13:57:02 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * Function to malloc and init the propertis of <t_philo> type
 * Description:
 * - The id starts at 0
 * - The fork partition is based on the <id> of the philosopher
 * - The left fork is equal to (id) and the right fork is qeual to (id + 1)
 * - The last philosopher with have the reverse order 
 * of left and right forks to avoid circular picking 
 * where all philosphers pick the left forks first.
 */
static int	ft_philos_init(t_program *prog)
{
	int	i;
	int	nth;

	i = -1;
	while (++i < prog->philo_count)
	{
		prog->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!prog->philos[i])
			return (error_msg_ret("Failed to malloc type (t_philo *)\n", &prog->mt_lock_print, 0));
		memset(prog->philos[i], 0, sizeof(t_philo));
		prog->philos[i]->id = i;
		prog->philos[i]->philo_count = prog->philo_count;
		prog->philos[i]->mt_lock_dead = &prog->mt_lock_dead;
		prog->philos[i]->mt_lock_meal = &prog->mt_lock_meal;
		prog->philos[i]->mt_lock_print = &prog->mt_lock_print;
		prog->philos[i]->start_ms = get_current_time(&prog->mt_lock_print);
		prog->philos[i]->last_meal_ms = prog->philos[i]->start_ms;
		prog->philos[i]->time_die = prog->time_die;
		prog->philos[i]->time_sleep = prog->time_sleep;
		prog->philos[i]->time_eat = prog->time_eat;
		nth = ft_min(i, (i + 1) % prog->philo_count);
		prog->philos[i]->left_fork = &prog->mt_forks[nth];
		nth = ft_max(i, (i + 1) % prog->philo_count);
		prog->philos[i]->right_fork = &prog->mt_forks[nth];
	}
	return (1);
}

/**
 * Function to init all the mutexes in the program
 * List of mutexes:
 * <1> mt_lock_meal
 * <2> mt_lock_print
 * <3> mt_forks (array of mutexes)
 */
static int	ft_mutexes_init(t_program *prog)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&prog->mt_lock_meal, NULL)
		|| pthread_mutex_init(&prog->mt_lock_print, NULL)
		|| pthread_mutex_init(&prog->mt_lock_dead, NULL))
	{
		return (error_msg_ret("Failed to init mutex\n", &prog->mt_lock_print ,0));
	}
	while (i < prog->philo_count)
	{
		if (pthread_mutex_init(&prog->mt_forks[i], NULL))
			return (error_msg_ret("Failed to init mutex\n", &prog->mt_lock_print ,0));
		++i;
	}
	return (1);
}

int	ft_init(int ac, char **av, t_program *prog)
{
	prog->terminate = 0;
	prog->ac = ac;
	prog->av = av;
	prog->philo_count = (int) ft_atold(av[1]);
	prog->time_die = ft_atold(av[2]);
	prog->time_eat = ft_atold(av[3]);
	prog->time_sleep = ft_atold(av[4]);
	if (ac == 6)
		prog->must_eat = ft_atold(av[5]);
	//------------------------------
	// INIT MUTECES;
	//------------------------------
	prog->mt_forks = (t_mutex *)
		ft_calloc(prog->philo_count + 1, sizeof(t_mutex));
	if (!prog->mt_forks)
		return (0);
	if (!ft_mutexes_init(prog))
		return (0);
	//------------------------------
	// INIT PHILOS;
	//------------------------------
	prog->philos = (t_philo **)
		ft_calloc((prog->philo_count + 1), sizeof(t_philo *));
	if (!prog->philos)
		return (0);
	if (!ft_philos_init(prog))
		return (0);
	return (1);
}
