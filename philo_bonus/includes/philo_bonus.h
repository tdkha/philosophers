/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:46:05 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/05 13:51:54 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <limits.h>
# include <stdio.h> 
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>

//--------------------------------------------------
// RE_DEFINITION
//--------------------------------------------------

# define PHILO_FULL 42
# define PHILO_DEAD 24

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

//--------------------------------------------------
// STRUCT
//--------------------------------------------------

/**
 * Struct for each philosopher
 * @param sem_shared a shared semaphore to be used among general functions
 * @param sem_terminate a semaphore to check for the <termination> variable
 */
typedef struct s_philo
{
	int					id;
	int					meal_eaten;
	int					philo_count;
	int					terminate;
	char				sem_ter_name[80];
	char				sem_shared_name[80];
	sem_t				*sem_terminate;
	sem_t				*sem_shared;
	pid_t				pid;
	size_t				last_meal_ms;
	size_t				start_ms;
	struct s_program	*prog;
}	t_philo;

/**
 * Struct for a shared data in a program
 * @param ac argument count
 * @param av argument vector
 * @param philo_count a total number of philosophers
 * @param must_eat a number of meals one philisopher should eat (if specified)
 * @param time_die interval for lifespan if not eating
 * @param time_eat tike for eating
 * @param time_sleep time for sleeping
 * @param philos array of philosophers
 * @param sem_shared a shared semaphore to be used among general functions
 * @param sem_forks a semephore representing forks 
 * 
 */
typedef struct s_program
{
	int			ac;
	char		**av;
	int			philo_count;
	int			must_eat;
	size_t		time_die;
	size_t		time_eat;
	size_t		time_sleep;
	t_philo		**philos;
	sem_t		*sem_forks;
	sem_t		*sem_print;
}	t_program;

//--------------------------------------------------
// LIBFT
//--------------------------------------------------

int		ft_isdigit(int c);
int		ft_isspace(int c);
size_t	ft_strlen(const char *s);
long	ft_atold(const char *str);
void	*ft_calloc(size_t count, size_t size);

//--------------------------------------------------
// UTILS
//--------------------------------------------------

size_t	get_current_time(void);
void	ft_usleep(size_t milliseconds, t_philo *philo);
int		ft_make_sem(t_philo *philo, int i);
//--------------------------------------------------
// PRINT MESSAGE
//--------------------------------------------------

void	error_msg(char *str);
int		error_msg_ret(char *str, int val);
int		philo_msg(t_philo *philo, char *str);

//--------------------------------------------------
// PROGRAM UTILS
//--------------------------------------------------

int		ft_init(int ac, char **av, t_program *prog);
int		ft_free(t_program *prog);
int		ft_philos_clean(t_program *prog);
void	ft_kill_processes(t_program *prog);

//--------------------------------------------------
//	PROCESS
//--------------------------------------------------
int		create_process(t_program *prog);
void	end_process_clean(t_philo *philo);
int		end_process_exit(char *str, int exit_code);
void	wait_process(t_program *prog);

//--------------------------------------------------
// ROUTINE
//--------------------------------------------------

int		ft_check_terminate(t_philo *philo);
int		ft_pick_forks(t_philo *philo);
int		ft_eat(t_philo *philo);
int		ft_sleep_think(t_philo *philo);
void	*philo_routine(void *v_philo);
int		monitor_routine(t_philo *philo);

//--------------------------------------------------
// MAIN PROGRAM
//--------------------------------------------------

int		ft_arg_check(int ac, char **av);

#endif