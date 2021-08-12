/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:33:44 by agidget           #+#    #+#             */
/*   Updated: 2021/08/08 18:33:49 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(struct timeval start, t_philo *phil, int msg)
{
	long	cur_time;

	pthread_mutex_lock(&(phil->info->print));
	if (phil->info->end_flag == 0)
	{
		cur_time = time_passed(&start);
		if (msg == FORK)
			printf("%.f %d has taken a fork\n", cur_time * 1e-3, phil->num);
		if (msg == EAT)
			printf("%.f %d is eating\n", cur_time * 1e-3, phil->num);
		if (msg == SLEEP)
			printf("%.f %d is sleeping\n", cur_time * 1e-3, phil->num);
		if (msg == THINK)
			printf("%.f %d is thinking\n", cur_time * 1e-3, phil->num);
		pthread_mutex_unlock(&(phil->info->print));
	}
	else
		pthread_mutex_unlock(&(phil->info->print));
}

void	philo_ate(t_philo *phil, t_gen *info)
{
	phil->ate_num++;
	if (phil->ate_num == info->q_to_eat)
		info->who_ate++;
	if (info->who_ate == info->qnt)
	{
		info->end_flag = 1;
		pthread_mutex_lock(&(info->print));
		printf("All philos ate %d times\n", info->q_to_eat);
		return ;
	}	
}

void	eating(t_philo *phil, t_gen *info, struct timeval start)
{
	pthread_mutex_lock(&(info->forks[left(phil)]));
	print_msg(start, phil, FORK);
	pthread_mutex_lock(&(info->forks[right(phil)]));
	print_msg(start, phil, FORK);
	print_msg(start, phil, EAT);
	phil->last_meal = time_passed(&start);
	my_sleep(phil, start, EAT);
	philo_ate(phil, info);
	pthread_mutex_unlock(&(info->forks[left(phil)]));
	pthread_mutex_unlock(&(info->forks[right(phil)]));
}

void	*philos(void *args)
{
	t_philo			*phil;
	t_gen			*info;
	struct timeval	start;

	phil = (t_philo *)args;
	info = phil->info;
	gettimeofday(&start, NULL);
	if (phil->num % 2 == 0)
		usleep(40);
	while (info->end_flag == 0)
	{
		eating(phil, info, start);
		print_msg(start, phil, SLEEP);
		my_sleep(phil, start, SLEEP);
		print_msg(start, phil, THINK);
		usleep(80);
	}
	return (NULL);
}
