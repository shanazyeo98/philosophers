/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:55:21 by shayeo            #+#    #+#             */
/*   Updated: 2024/09/19 15:52:02 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	releaseforks(t_philo *philo, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		sem_post(philo->sem_forks);
		j++;
	}
}

void	lockforks(t_philo *philo)
{
	struct timeval	t_fork1;

	sem_wait(philo->sem_forks);
	gettimeofday(&t_fork1, NULL);
	print(FORK, t_fork1, philo);
	if (philo->n_philo > 1)
	{
		sem_wait(philo->sem_forks);
		gettimeofday(&t_fork1, NULL);
		print(FORK, t_fork1, philo);
	}
}

void	eating(t_philo *philo)
{
	struct timeval	t_eat;

	gettimeofday(&t_eat, NULL);
	sem_wait(philo->sem_status);
	philo->ts_ate = t_eat;
	philo->n_ate++;
	sem_post(philo->sem_status);
	print(EAT, t_eat, philo);
	usleep(philo->t_eat * 1000);
	releaseforks(philo, 2);
}

void	startmeal(t_philo *philo, int *check)
{
	lockforks(philo);
	if (philo->n_philo > 1)
		eating(philo);
	else
		*check = 1;
}
