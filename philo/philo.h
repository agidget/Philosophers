/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:36:31 by agidget           #+#    #+#             */
/*   Updated: 2021/08/11 16:15:22 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/errno.h>
# include <fcntl.h>
# include <sys/time.h>

# define EAT 0
# define SLEEP 1
# define THINK 2
# define FORK 3

typedef struct s_gen
{
	int				qnt;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				q_to_eat;
	int				who_ate;
	int				end_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_t		death;
}	t_gen;

typedef struct s_philo
{
	int			num;
	long		last_meal;
	int			ate_num;
	pthread_t	th;
	t_gen		*info;
}	t_philo;

int		ft_atoi(const char *str, int *flag);
long	time_passed(struct timeval *start);
void	my_sleep(t_philo *phil, struct timeval start, int process);
int		init_info(t_gen *info, char **argv, int argc);
void	mutex_initial(t_gen *info);
void	mutex_destroy(t_gen *info);
void	thread_creation(t_philo *philo, t_gen *info);
void	thread_joining(t_gen *info);
void	part_of_main(t_philo *philo, t_gen *info, pthread_mutex_t *forks);
void	*philos(void *args);
void	*if_dead(void *args);
int		left(t_philo *phil);
int		right(t_philo *phil);
void	print_msg(struct timeval start, t_philo *phil, int msg);
void	philo_ate(t_philo *phil, t_gen *info);
void	eating(t_philo *phil, t_gen *info, struct timeval start);
void	dead_msg(t_philo *phil, t_gen *info, int cur_time, int i);
void	free_info(t_gen *info);
int		check_args(t_gen *info, int flag);

#endif
