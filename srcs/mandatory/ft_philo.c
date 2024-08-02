/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:06:33 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/01 22:23:26 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * Function to put a single fork. The order of picking fork of the last philo willl be different.
 * 
 * Explantation:
 * 
 * - Philo 0:
 * 	ft_min(0, 1) -> 0 (pick left fork)
 * 	ft_max(0, 1 % 5) -> 1 (pick right fork)
 * 
 * - Philo 5 (max):
 * 	ft_min(4, (4 + 1) % 5) -> 0 (pick right fork)
 * 	ft_max(4, (4 + 1) % 5) -> 4 (pick left fork)
 */

static void ft_put_fork(t_philo *philo, t_philo_status status, int nth_fork) {
    int actual_fork;

    actual_fork = nth_fork;
    if (status == FORK_UP_L || status == FORK_DOWN_L)
        actual_fork = ft_min(nth_fork, (nth_fork + 1) % philo->prog->philo_count);
    else if (status == FORK_UP_R || status == FORK_DOWN_R)
        actual_fork = ft_max(nth_fork, (nth_fork + 1) % philo->prog->philo_count);
    
    if ((status == FORK_UP_L || status == FORK_UP_R) && actual_fork >= 0)
        pthread_mutex_lock(&philo->prog->mt_forks[actual_fork]);
    else if ((status == FORK_DOWN_L || status == FORK_DOWN_R) && actual_fork >= 0)
        pthread_mutex_unlock(&philo->prog->mt_forks[actual_fork]);
    
    philo_msg(philo, status);
}

static void ft_eat(t_philo *philo, t_program *prog, int nth_fork)
{
	// pthread_mutex_lock(philo->left_fork);
    // if (prog->philo_count == 1) {
    //     pthread_mutex_unlock(philo->left_fork);
    //     ft_usleep(prog->time_die, prog);
    //     return;
    // }
    // // Pick up right fork
    // pthread_mutex_lock(philo->right_fork);

    // // Eating
    // philo->eating = 1;
    // philo_msg(philo, EAT);
    // pthread_mutex_lock(&prog->mt_lock_meal);
    // philo->last_meal_ms = get_current_time(prog);
    // philo->meal_eaten++;
    // pthread_mutex_unlock(&prog->mt_lock_meal);
    // ft_usleep(prog->time_eat, prog);
    // philo->eating = 0;

    // // Put down left fork
    // pthread_mutex_unlock(philo->left_fork);
    // // Put down right fork
    // pthread_mutex_unlock(philo->right_fork);

	ft_put_fork(philo, FORK_UP_L, philo->id);
    if (prog->philo_count == 1) {
        ft_put_fork(philo, FORK_DOWN_L, philo->id);
        ft_usleep(prog->time_die, prog);
        return;
    }
    ft_put_fork(philo, FORK_UP_R, philo->id);
    philo->eating = 1;
    philo_msg(philo, EAT);
    pthread_mutex_lock(&prog->mt_lock_meal);
    philo->last_meal_ms = get_current_time(prog);
    philo->meal_eaten++;
    pthread_mutex_unlock(&prog->mt_lock_meal);
    ft_usleep(prog->time_eat, prog);
    philo->eating = 0;
	ft_put_fork(philo, FORK_DOWN_L, philo->id);
	ft_put_fork(philo, FORK_DOWN_R, philo->id);
}

void ft_philo(t_philo *philo, t_program *prog, t_philo_status status, int nth_fork) {
    if (status == EAT && nth_fork >= 0) {
        ft_eat(philo, prog, nth_fork);
    } else if (status == SLEEP) {
        philo_msg(philo, SLEEP);
        ft_usleep(philo->prog->time_sleep, philo->prog);
    } else if (status == THINK) {
        philo_msg(philo, THINK);
    }
}