/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:49:09 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/13 12:50:19 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * - The fork partition is based on the <id> of the philosopher
 * - The left fork is equal to (id) and the right fork is qeual to (id + 1)
 * - The last philosopher with have the reverse order 
 * of left and right forks to avoid circular picking 
 * where all philosphers pick the left forks first.
 */
static void	ft_fork_assign(t_program *prog, int i)
{
	prog->philos[i]->left_fork = &prog->mt_forks[i];
	prog->philos[i]->right_fork = &prog->mt_forks[(i + 1) % prog->philo_count];
}

/**
 * Function to malloc and init the propertis of <t_philo> type
 * Description:
 * - The id starts at 0
 * 
 */
static int	ft_philos_init(t_program *prog)
{
	int	i;

	i = -1;
	while (++i < prog->philo_count)
	{
		prog->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!prog->philos[i])
			return (error_msg_ret("Failed to malloc type (t_philo *)\n",
					&prog->mt_lock, 0));
		memset(prog->philos[i], 0, sizeof(t_philo));
		prog->philos[i]->id = i;
		prog->philos[i]->philo_count = prog->philo_count;
		prog->philos[i]->must_eat = prog->must_eat;
		prog->philos[i]->terminate = &prog->terminate;
		prog->philos[i]->philo_full_count = &prog->philo_full_count;
		prog->philos[i]->mt_lock = &prog->mt_lock;
		prog->philos[i]->mt_print = &prog->mt_print;
		prog->philos[i]->start_ms = get_current_time();
		prog->philos[i]->last_meal_ms = prog->philos[i]->start_ms;
		prog->philos[i]->time_die = prog->time_die;
		prog->philos[i]->time_sleep = prog->time_sleep;
		prog->philos[i]->time_eat = prog->time_eat;
		ft_fork_assign(prog, i);
	}
	return (1);
}

/**
 * Function to init all the mutexes in the program
 * List of mutexes:
 * <1> mt_lock_meal
 * <2> mt_lock
 * <3> mt_forks (array of mutexes)
 */
static int	ft_mutexes_init(t_program *prog)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&prog->mt_lock, NULL))
	{
		return (error_msg_ret("Failed to init mutex\n",
				&prog->mt_lock, 0));
	}
	if (pthread_mutex_init(&prog->mt_print, NULL))
	{
		return (error_msg_ret("Failed to init mutex\n",
				&prog->mt_lock, 0));
	}
	while (i < prog->philo_count)
	{
		if (pthread_mutex_init(&prog->mt_forks[i], NULL))
			return (error_msg_ret("Failed to init mutex\n",
					&prog->mt_lock, 0));
		++i;
	}
	return (1);
}

static int	ft_alloc(t_program *prog)
{
	prog->mt_forks = (t_mutex *)
		ft_calloc(prog->philo_count + 1, sizeof(t_mutex));
	if (!prog->mt_forks)
		return (0);
	prog->philos = (t_philo **)
		ft_calloc((prog->philo_count + 1), sizeof(t_philo *));
	if (!prog->philos)
		return (0);
	return (1);
}

int	ft_init(int ac, char **av, t_program *prog)
{
	memset(prog, 0, sizeof(t_program));
	prog->ac = ac;
	prog->av = av;
	prog->philo_count = (int) ft_atold(av[1]);
	prog->time_die = ft_atold(av[2]);
	prog->time_eat = ft_atold(av[3]);
	prog->time_sleep = ft_atold(av[4]);
	if (prog->time_eat > prog->time_die)
		prog->time_eat = prog->time_die + 6;
	if (prog->time_sleep > prog->time_die)
		prog->time_sleep = prog->time_die + 6;
	if (ac == 6)
		prog->must_eat = ft_atold(av[5]);
	else
		prog->must_eat = -1;
	if (!ft_alloc(prog))
		return (0);
	if (!ft_mutexes_init(prog))
		return (0);
	if (!ft_philos_init(prog))
		return (0);
	return (1);
}
