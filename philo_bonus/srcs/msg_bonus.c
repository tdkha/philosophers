/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:17:18 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/13 09:16:59 by ktieu            ###   ########.fr       */
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

void write_msg(size_t time, int id, const char *msg)
{
    char	buffer[420];
    char	time_str[20];
    char	id_str[10];
    int		len;
    int		i;

	len = 0;
	i = 0;
    ultoa(time, time_str);
    for (i = 0; time_str[i] != '\0'; i++)
        buffer[len++] = time_str[i];
    buffer[len++] = ' ';
    itoa(id, id_str);
    for (i = 0; id_str[i] != '\0'; i++)
        buffer[len++] = id_str[i];
    buffer[len++] = ' ';
    for (i = 0; msg[i] != '\0'; i++)
    {
		buffer[len++] = msg[i];
	}
    buffer[len++] = '\n';
    (void)!write(STDOUT_FILENO, buffer, len);
}


// int	philo_msg(t_philo *philo, char *str)
// {
// 	size_t	time;

// 	time = get_current_time() - philo->start_ms;
// 	if (sem_wait(philo->prog->sem_print) != 0)
// 	{
// 		error_msg("Error: philo_msg from sem_wait()\n");
// 		return (0);
// 	}
// 	write_msg(time, philo->id +1, str);
// 	if (sem_post(philo->prog->sem_print) != 0)
// 	{
// 		error_msg("Error: philo_msg from sem_post()\n");
// 		return (0);
// 	}
// 	return (1);
// }

int	philo_msg(t_philo *philo, char *str)
{
	size_t	time;

	time = get_current_time() - philo->start_ms;
	sem_wait(philo->prog->sem_print);
	write_msg(time, philo->id +1, str);
	sem_post(philo->prog->sem_print);
	return (1);
}
