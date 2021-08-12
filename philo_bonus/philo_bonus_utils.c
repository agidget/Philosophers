/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:31:52 by agidget           #+#    #+#             */
/*   Updated: 2021/08/11 15:31:54 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	my_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

static int	int_error(void)
{
	printf("Invalid arguments, please, try again\n");
	exit(EXIT_FAILURE);
}

int	ft_atoi(const char *str, int *flag)
{
	int			i;
	int			sign;
	long int	num;

	i = 0;
	while (str[i] && my_isspace(str[i]))
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	num = 0;
	if (!(str[i] >= '0' && str[i] <= '9'))
		*flag = 1;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		num = num * 10 + str[i++] - '0';
	if (str[i] != '\0')
		int_error();
	if (num * sign > 2147483647 || num * sign < -2147483648)
		int_error();
	return (num * sign);
}
