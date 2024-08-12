/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:17:27 by ktieu             #+#    #+#             */
/*   Updated: 2024/08/13 01:04:38 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void itoa(int n, char *str)
{
    int i = 0;
    int start = 0;
    int sign = n;

    if (n == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    if (sign < 0) {
        n = -n;
    }
    while (n > 0) {
        str[i++] = (n % 10) + '0';
        n /= 10;
    }
    if (sign < 0) {
        str[i++] = '-';
    }
    str[i] = '\0';
    for (start = 0, --i; start < i; ++start, --i)
	{
        char temp = str[start];
        str[start] = str[i];
        str[i] = temp;
    }
}

void ultoa(size_t n, char *str)
{
    int i = 0;
    int start;

    if (n == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    while (n > 0) {
        str[i++] = (n % 10) + '0';
        n /= 10;
    }
    str[i] = '\0';
    for (start = 0, --i; start < i; ++start, --i)
	{
        char temp = str[start];
        str[start] = str[i];
        str[i] = temp;
    }
}