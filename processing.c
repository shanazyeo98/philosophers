/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:08:30 by shayeo            #+#    #+#             */
/*   Updated: 2024/09/19 16:35:38 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_strlen(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr != NULL && nptr[i] != '\0')
		i++;
	return (i);
}

int	ft_isdigit(int a)
{
	if (!(a >= '0' && a <= '9'))
		return (0);
	return (1);
}

long	ft_atoi(const char *nptr)
{
	int		sign;
	int		i;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i += 1;
	}
	while (ft_isdigit(nptr[i]) != 0 && nptr[i] != '\0')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	if (i == 0 || nptr[i] != '\0' || result * sign > INT_MAX \
	|| result * sign < 0)
		return (-1);
	return (result * sign);
}

int	checkparams(t_philo *dets, int argc)
{
	if (dets->n_philo <= 0 || dets->n_philo > 10000 || dets->t_die < 0 \
	|| dets->t_eat < 0 || dets->t_sleep < 0 || (argc == 6 && dets->n_eat <= 0))
	{
		write(2, "Error: Please provide valid values.\n", 36);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	preprocessing(t_philo *dets, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Please provide the appropriate no. of arguments\n", 48);
		return (EXIT_FAILURE);
	}
	dets->n_philo = ft_atoi(argv[1]);
	dets->t_die = ft_atoi(argv[2]);
	dets->t_eat = ft_atoi(argv[3]);
	dets->t_sleep = ft_atoi(argv[4]);
	dets->n_eat = 0;
	dets->pids = NULL;
	dets->status = ALIVE;
	dets->n_ate = 0;
	dets->index = 0;
	dets->ts_ate.tv_sec = 0;
	dets->start.tv_sec = 0;
	dets->sem_ate = NULL;
	dets->sem_death = NULL;
	dets->sem_forks = NULL;
	dets->sem_print = NULL;
	dets->sem_status = NULL;
	if (argc == 6)
		dets->n_eat = ft_atoi(argv[5]);
	return (checkparams(dets, argc));
}
