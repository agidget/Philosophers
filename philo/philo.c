/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:35:40 by agidget           #+#    #+#             */
/*   Updated: 2021/08/11 16:27:49 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dead_msg(t_philo *phil, t_gen *info, int cur_time, int i)
{
	info->end_flag = 1;
	pthread_mutex_lock(&(info->print));
	printf("%.f %d died\n", cur_time * 1e-3, phil[i].num);
}

void	*if_dead(void *args)
{
	t_philo			*phil;
	t_gen			*info;
	struct timeval	start;
	int				i;
	int				cur_time;

	phil = (t_philo *)args;
	info = phil->info;
	gettimeofday(&start, NULL);
	while (1)
	{
		i = -1;
		cur_time = time_passed(&start);
		while (++i < info->qnt)
		{
			if (info->end_flag == 1)
				return (NULL);
			if (cur_time - phil[i].last_meal > info->t_die * 1e3)
			{
				dead_msg(phil, info, cur_time, i);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	part_of_main(t_philo *philo, t_gen *info, pthread_mutex_t *forks)
{
	philo->info = info;
	info->forks = forks;
	mutex_initial(info);
	thread_creation(philo, info);
	thread_joining(info);
	mutex_destroy(info);
	free(info);
	free(philo);
	free(forks);
}

void	free_info(t_gen *info)
{
	printf("Error with malloc\n");
	free(info);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_gen			*info;
	pthread_mutex_t	*forks;

	info = malloc(sizeof(t_gen));
	if (init_info(info, argv, argc) == -1)
	{
		printf("Error with arguments\n");
		return (1);
	}
	philo = malloc(sizeof(t_philo) * info->qnt);
	if (!philo)
	{
		free_info(info);
		return (2);
	}
	forks = malloc(sizeof(pthread_mutex_t) * info->qnt);
	if (!forks)
	{
		free_info(info);
		free(philo);
		return (2);
	}
	part_of_main(philo, info, forks);
}
