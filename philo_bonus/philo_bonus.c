/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:31:59 by agidget           #+#    #+#             */
/*   Updated: 2021/08/11 15:33:43 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	semaphore_unlinks(void)
{
	sem_unlink("sem1");
	sem_unlink("sem2");
	sem_unlink("sem3");
	sem_unlink("sem4");
	sem_unlink("sem5");
}

void	semaphore_creation(t_gen *info)
{
	info->semaphore = sem_open("sem1", O_CREAT | O_EXCL, 0644, info->qnt);
	info->sem_print = sem_open("sem2", O_CREAT | O_EXCL, 0644, 1);
	info->sem_dead = sem_open("sem3", O_CREAT | O_EXCL, 0644, 1);
	info->sem_ate = sem_open("sem4", O_CREAT | O_EXCL, 0644, 1);
	info->sem_one = sem_open("sem5", O_CREAT | O_EXCL, 0644, 1);
}

void	semaphore_closes(t_gen *info)
{
	sem_close(info->semaphore);
	sem_close(info->sem_print);
	sem_close(info->sem_dead);
	sem_close(info->sem_ate);
	sem_close(info->sem_one);
}

int	main(int argc, char **argv)
{
	t_philo			*phil;
	t_gen			*info;
	struct timeval	start;

	semaphore_unlinks();
	if (argc != 5 && argc != 6)
	{
		printf("Please enter the right number of arguments\n");
		exit(EXIT_FAILURE);
	}
	info = NULL;
	info = init_info(info, argv);
	phil = NULL;
	phil = init_philo(phil, info);
	semaphore_creation(info);
	gettimeofday(&start, NULL);
	philo(phil, info, start);
	semaphore_closes(info);
	semaphore_unlinks();
	free(phil);
	free(info);
}
