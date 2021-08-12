/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:31:19 by agidget           #+#    #+#             */
/*   Updated: 2021/08/11 15:32:33 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_error(t_gen *info)
{
	free(info);
	printf("Invalid arguments, please, try again\n");
	exit(EXIT_FAILURE);
}

void	error_arg(t_gen *info, int flag)
{
	if (flag != 0 || info->qnt <= 0 || info->t_die <= 0
		|| info->t_eat <= 0 || info->t_sleep <= 0)
		print_error(info);
}

t_gen	*init_info(t_gen *info, char **argv)
{
	int	flag;

	info = malloc(sizeof(t_gen));
	if (!info)
	{
		printf("Error with malloc\n");
		exit(EXIT_FAILURE);
	}
	flag = 0;
	info->qnt = ft_atoi(argv[1], &flag);
	info->t_die = ft_atoi(argv[2], &flag);
	info->t_eat = ft_atoi(argv[3], &flag);
	info->t_sleep = ft_atoi(argv[4], &flag);
	error_arg(info, flag);
	if (argv[5])
	{
		info->q_to_eat = ft_atoi(argv[5], &flag);
		if (flag != 0 || info->q_to_eat <= 0)
			print_error(info);
	}
	else
		info->q_to_eat = -1;
	return (info);
}

long	time_passed(struct timeval *start)
{
	long			passed;
	struct timeval	end;

	gettimeofday(&end, NULL);
	passed = (end.tv_sec * 1e6 + end.tv_usec)
		- (start->tv_sec * 1e6 + start->tv_usec);
	return (passed);
}
