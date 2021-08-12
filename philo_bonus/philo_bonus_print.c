/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:31:44 by agidget           #+#    #+#             */
/*   Updated: 2021/08/11 16:32:47 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_dead(t_philo *phil, long cur_time, int i)
{
	sem_wait(phil->info->sem_dead);
	if (cur_time - phil[i].last_meal > phil->info->t_die * 1e3)
	{
		printf("%.f %d died\n", cur_time * 1e-3, phil[i].num);
		exit(1);
	}
	else
		sem_post(phil->info->sem_dead);
}

void	my_sleep(t_philo *phil, struct timeval start, int process, int i)
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
	while (cur_time < time_to)
	{
		usleep(50);
		cur_time = time_passed(&start);
		print_dead(phil, cur_time, i);
	}
}

void	all_ate(t_philo *phil, int i)
{
	phil[i].ate_num++;
	sem_wait(phil->info->sem_ate);
	if ((i == phil->info->qnt - 1) && phil[i].ate_num == phil->info->q_to_eat)
	{
		printf("All philos ate %d times\n", phil->info->q_to_eat);
		exit(EXIT_SUCCESS);
	}
	else
		sem_post(phil->info->sem_ate);
}

void	one_philo(struct timeval start, t_philo *phil, int i)
{
	long	cur_time;

	sem_wait(phil->info->sem_one);
	if (phil->info->qnt == 1)
	{
		cur_time = time_passed(&start);
		while (cur_time < phil->info->t_die * 1e3)
		{
			usleep(50);
			cur_time = time_passed(&start);
		}
		printf("%.f %d died\n", cur_time * 1e-3, phil[i].num);
		exit(EXIT_SUCCESS);
	}
	else
		sem_post(phil->info->sem_one);
}

void	print_status(struct timeval start, t_philo *phil, int i, int msg)
{
	long	cur_time;

	sem_wait(phil->info->sem_print);
	cur_time = time_passed(&start);
	print_dead(phil, cur_time, i);
	if (msg == FORK1)
	{
		printf("%.f %d has taken a fork\n", cur_time * 1e-3, phil[i].num);
		one_philo(start, phil, i);
	}
	if (msg == FORK2)
		printf("%.f %d has taken a fork\n", cur_time * 1e-3, phil[i].num);
	if (msg == EAT)
	{
		printf("%.f %d is eating\n", cur_time * 1e-3, phil[i].num);
		phil[i].last_meal = cur_time;
	}
	if (msg == SLEEP)
	{
		all_ate(phil, i);
		printf("%.f %d is sleeping\n", cur_time * 1e-3, phil[i].num);
	}
	if (msg == THINK)
		printf("%.f %d is thinking\n", cur_time * 1e-3, phil[i].num);
	sem_post(phil->info->sem_print);
}
