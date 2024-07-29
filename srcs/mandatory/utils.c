/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:22:53 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/27 15:36:05 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

size_t	get_current_time(t_program *prog)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error_msg(prog, "Error occurred when calling <gettimeofday>\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds, t_program *prog)
{
	size_t	start;

	start = get_current_time(prog);
	while ((get_current_time(prog) - start) < milliseconds)
		usleep(500);
	return (0);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

// void	ft_swap_num_array(t_philo **nums, int i, int j)
// {
// 	t_philo	*tmp;

// 	tmp = nums[i];
// 	nums[i] = nums[j];
// 	nums[j] = tmp;
// }

// static int	partition(t_philo **arr, int left, int right)
// {
// 	int	pivot_num;
// 	int	i;
// 	int	j;

// 	pivot_num = arr[left]->last_meal_ms;
// 	i = left;
// 	j = right;
// 	while (i <= j)
// 	{
// 		while (i <= j && arr[i]->last_meal_ms <= pivot_num)
// 			i++;
// 		while (i <= j && arr[j]->last_meal_ms >= pivot_num)
// 			j--;
// 		if (i < j)
// 			ft_swap_num_array(arr, i, j);
// 	}
// 	ft_swap_num_array(arr, left, j);
// 	return (j);
// }

// void	ft_quick_sort(t_philo **arr, int left, int right)
// {
// 	int	pivot_index;

// 	if (left < right)
// 	{
// 		pivot_index = partition(arr, left, right);
// 		ft_quick_sort(arr, left, pivot_index - 1);
// 		ft_quick_sort(arr, pivot_index + 1, right);
// 	}
// }
