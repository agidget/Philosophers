/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_life.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:31:36 by agidget           #+#    #+#             */
/*   Updated: 2021/08/11 15:34:11 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_life(t_philo *phil, t_gen *info, struct timeval start, int i)
{
	while (1)
	{
		sem_wait(info->semaphore);
		print_status(start, phil, i, FORK1);
		sem_wait(info->semaphore);
		print_status(start, phil, i, FORK2);
		print_status(start, phil, i, EAT);
		my_sleep(phil, start, EAT, i);
		sem_post(info->semaphore);
		sem_post(info->semaphore);
		print_status(start, phil, i, SLEEP);
		my_sleep(phil, start, SLEEP, i);
		print_status(start, phil, i, THINK);
	}
}

void	philo(t_philo *phil, t_gen *info, struct timeval start)
{
	int		i;

	i = 0;
	while (i < info->qnt)
	{
		if (i > info->qnt / 2 - 1)
			usleep(40);
		phil[i].pid = fork();
		if (phil[i].pid == 0)
		{
			philo_life(phil, info, start, i);
		}
		i++;
	}
	waitpid(0, NULL, 0);
	i = 0;
	while (i < info->qnt)
	{
		kill(phil[i].pid, SIGKILL);
		i++;
	}
}

t_philo	*init_philo(t_philo	*phil, t_gen *info)
{
	int	i;

	phil = malloc(sizeof(t_philo) * info->qnt);
	if (!phil)
	{
		printf("Error with malloc\n");
		exit(EXIT_FAILURE);
	}
	phil->info = info;
	i = 0;
	while (i < info->qnt)
	{
		phil[i].num = i + 1;
		phil[i].last_meal = 0;
		phil[i].ate_num = 0;
		i++;
	}
	return (phil);
}
