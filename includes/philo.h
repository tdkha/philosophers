/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:46:05 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/01 23:01:22 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <stdio.h> 
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

//--------------------------------------------------
// RE_DEFINITION
//--------------------------------------------------

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

//--------------------------------------------------
// STRUCT
//--------------------------------------------------

typedef enum s_philo_status
{
	FORK_UP_L,
	FORK_UP_R,
	FORK_DOWN_L,
	FORK_DOWN_R,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_philo_status;

typedef struct s_philo
{
	int					id;
	int					died;
	int					eating;
	int					meal_eaten;
	size_t				last_meal_ms;
	size_t				start_ms;
	t_thread			pth;
	t_mutex				*left_fork;
	t_mutex				*right_fork;
	t_mutex				*mt_lock_meal;
	t_mutex				*mt_lock_print;
	t_mutex				*mt_lock_dead;
}	t_philo;

typedef struct s_program
{
	int			ac;
	char		**av;
	int			philo_count;
	int			must_eat;
	size_t		time_die;
	size_t		time_eat;
	size_t		time_sleep;
	t_mutex		mt_lock_meal;
	t_mutex		mt_lock_print;
	t_mutex		mt_lock_dead;
	t_mutex		*mt_forks;
	t_philo		**philos;
	t_thread	pth_monitor;
	int			terminate;
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

size_t	get_current_time(t_program *prog);
int		ft_usleep(size_t milliseconds, t_program *prog);
int		ft_min(int a, int b);
int		ft_max(int a, int b);

//--------------------------------------------------
// PRINT MESSAGE
//--------------------------------------------------

void	error_msg(t_program *prog, char *str);
int		error_msg_ret(t_program *prog, char *str, int return_val);
void	philo_msg(t_philo *philo, t_philo_status status);

//--------------------------------------------------
// PROGRAM UTILS
//--------------------------------------------------

int		ft_init(int ac, char **av, t_program *prog);
int		ft_free(t_program *prog);

//--------------------------------------------------
// THREAD AND MUTEX
//--------------------------------------------------

void	*monitor(void *v_prog);
void	*philosopher(void * v_philo);
//--------------------------------------------------
// MAIN PROGRAM
//--------------------------------------------------

int		ft_arg_check(int ac, char **av);
int		philosopher(t_program *prog);

#endif