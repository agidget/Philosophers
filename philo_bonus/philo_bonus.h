/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:31:11 by agidget           #+#    #+#             */
/*   Updated: 2021/08/11 15:35:29 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

# define EAT 0
# define SLEEP 1
# define THINK 2
# define FORK1 3
# define FORK2 4

typedef struct s_gen
{
	int		qnt;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		q_to_eat;
	sem_t	*semaphore;
	sem_t	*sem_print;
	sem_t	*sem_dead;
	sem_t	*sem_ate;
	sem_t	*sem_one;
}	t_gen;

typedef struct s_philo
{
	int		num;
	long	last_meal;
	int		ate_num;
	pid_t	pid;
	t_gen	*info;
}	t_philo;

int		ft_atoi(const char *str, int *flag);
void	print_error(t_gen *info);
void	error_arg(t_gen *info, int flag);
t_gen	*init_info(t_gen *info, char **argv);
long	time_passed(struct timeval *start);
void	print_dead(t_philo *phil, long cur_time, int i);
void	my_sleep(t_philo *phil, struct timeval start, int process, int i);
void	all_ate(t_philo *phil, int i);
void	one_philo(struct timeval start, t_philo *phil, int i);
void	print_status(struct timeval start, t_philo *phil, int i, int msg);
void	philo_life(t_philo *phil, t_gen *info, struct timeval start, int i);
void	philo(t_philo *phil, t_gen *info, struct timeval start);
t_philo	*init_philo(t_philo	*phil, t_gen *info);
void	semaphore_unlinks(void);
void	semaphore_creation(t_gen *info);
void	semaphore_closes(t_gen *info);

#endif