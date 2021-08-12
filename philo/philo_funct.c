/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:27:43 by agidget           #+#    #+#             */
/*   Updated: 2021/08/08 18:28:06 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_passed(struct timeval *start)
{
	long			passed;
	struct timeval	end;

	gettimeofday(&end, NULL);
	passed = (end.tv_sec * 1e6 + end.tv_usec)
		- (start->tv_sec * 1e6 + start->tv_usec);
	return (passed);
}

void	my_sleep(t_philo *phil, struct timeval start, int process)
{
	long	cur_time;
	long	time_to;
	t_gen	*info;

	info = phil->info;
	cur_time = time_passed(&start);
	if (process == EAT)
		time_to = info->t_eat * 1e3 + cur_time;
	if (process == SLEEP)
		time_to = info->t_sleep * 1e3 + cur_time;
	while (cur_time < time_to && info->end_flag == 0)
	{
		if (cur_time - phil->last_meal > info->t_die * 1e3)
		{
			info->end_flag = 1;
			pthread_mutex_lock(&(info->print));
			printf("%.f %d died\n", cur_time * 1e-3, phil->num);
			pthread_mutex_unlock(&(info->print));
			return ;
		}
		usleep(50);
		cur_time = time_passed(&start);
	}
}

int	left(t_philo *phil)
{
	int	left;

	if (phil->num % 2 != 0)
		left = phil->num - 1;
	else
	{
		left = phil->num;
		if (phil->num == phil->info->qnt)
			left = 0;
	}
	return (left);
}

int	right(t_philo *phil)
{
	int	right;

	if (phil->num % 2 != 0)
	{
		right = phil->num;
		if (phil->num == phil->info->qnt)
			right = 0;
	}
	else
		right = phil->num - 1;
	return (right);
}
