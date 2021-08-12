/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:29:10 by agidget           #+#    #+#             */
/*   Updated: 2021/08/11 16:22:56 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(t_gen *info, int flag)
{
	if (flag != 0 || info->qnt <= 0 || info->t_die <= 0
		|| info->t_eat <= 0 || info->t_sleep <= 0
		|| info->q_to_eat < 0)
		return (-1);
	return (0);
}

int	init_info(t_gen *info, char **argv, int argc)
{
	int	flag;
	int	res;

	if (argc != 5 && argc != 6)
		return (-1);
	if (!info)
		return (-1);
	flag = 0;
	info->qnt = ft_atoi(argv[1], &flag);
	info->t_die = ft_atoi(argv[2], &flag);
	info->t_eat = ft_atoi(argv[3], &flag);
	info->t_sleep = ft_atoi(argv[4], &flag);
	if (argv[5])
		info->q_to_eat = ft_atoi(argv[5], &flag);
	else
		info->q_to_eat = 0;
	info->end_flag = 0;
	info->who_ate = 0;
	res = check_args(info, flag);
	if (res == -1)
		free(info);
	return (res);
}
