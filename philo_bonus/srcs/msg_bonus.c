/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:17:18 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/13 18:07:19 by ktieu            ###   ########.fr       */
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

static void	buffer_and_write(
	char *time_str,
	char *id_str,
	char *buffer,
	const char *msg)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (time_str[i] != '\0')
		buffer[len++] = time_str[i++];
	buffer[len++] = ' ';
	i = 0;
	while (id_str[i] != '\0')
		buffer[len++] = id_str[i++];
	buffer[len++] = ' ';
	i = 0;
	while (msg[i] != '\0')
		buffer[len++] = msg[i++];
	buffer[len++] = '\n';
	(void)!write(1, buffer, len);
}

void	write_msg(size_t time, int id, const char *msg)
{
	char	buffer[420];
	char	time_str[20];
	char	id_str[10];

	ultoa(time, time_str);
	itoa(id, id_str);
	buffer_and_write(time_str, id_str, buffer, msg);
}

int	philo_msg(t_philo *philo, char *str)
{
	size_t	time;

	time = get_current_time() - philo->start_ms;
	if (sem_wait(philo->prog->sem_print) != 0)
	{
		error_msg("philo_bonus: philo_msg: sem_wait()\n");
		return (0);
	}
	write_msg(time, philo->id +1, str);
	if (sem_post(philo->prog->sem_print) != 0)
	{
		error_msg("philo_bonus: philo_msg: sem_post()\n");
		return (0);
	}
	return (1);
}
