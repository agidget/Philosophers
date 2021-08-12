/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 16:13:35 by agidget           #+#    #+#             */
/*   Updated: 2021/08/11 16:13:51 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_initial(t_gen *info)
{
	int	i;

	i = 0;
	while (i < info->qnt)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL) != 0)
		{
			printf("Error with mutex initialization\n");
			return ;
		}
		i++;
	}
	if (pthread_mutex_init(&(info->print), NULL))
	{
		printf("Error with mutex initialization\n");
		return ;
	}
}

void	mutex_destroy(t_gen *info)
{
	int	i;

	i = 0;
	while (i < info->qnt)
	{
		pthread_mutex_destroy(&(info->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(info->print));
}

void	thread_creation(t_philo *philo, t_gen *info)
{
	int	i;

	i = 0;
	while (i < info->qnt)
	{
		philo[i].last_meal = 0;
		philo[i].ate_num = 0;
		philo[i].num = i + 1;
		philo[i].info = info;
		if (pthread_create(&(philo[i].th), NULL, philos, &philo[i]) != 0)
		{
			printf("Error with creating of threads\n");
			return ;
		}
		i++;
	}
	if (pthread_create(&(info->death), NULL, if_dead, philo) != 0)
	{
		printf("Error with creating of threads\n");
		return ;
	}
}

void	thread_joining(t_gen *info)
{
	if (pthread_join(info->death, NULL) != 0)
	{
		printf("Error with joining\n");
		return ;
	}
}
