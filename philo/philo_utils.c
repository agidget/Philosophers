/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agidget <agidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:34:08 by agidget           #+#    #+#             */
/*   Updated: 2021/08/11 16:24:06 by agidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	my_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
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
		return (-1);
	if (num * sign > 2147483647 || num * sign < -2147483648)
		return (-1);
	return (num * sign);
}
