/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shayeo <shayeo@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:45:36 by shayeo            #+#    #+#             */
/*   Updated: 2024/09/19 17:10:33 by shayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	mainproc(t_philo *dets)
{
	int	pid;
	int	status;

	while (1)
	{
		pid = waitpid(0, &status, 0);
		if (pid == -1)
			break ;
		if (WIFEXITED(status))
			sem_post(dets->sem_death);
	}
	pthread_join(dets->tr1, NULL);
	pthread_join(dets->tr2, NULL);
	clear(dets);
}

void	philoproc(t_philo *philo)
{
	free(philo->pids);
	initsemstatus(philo);
	createphilotr(philo);
	if (philo->index % 2 == 0)
		usleep(500);
	simulate(philo);
}

int	main(int argc, char *argv[])
{
	t_philo	dets;
	int		pid;

	if (preprocessing(&dets, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	initobjs(&dets);
	pid = createproc(&dets);
	if (pid != 0)
	{
		createmonitoring(&dets);
		mainproc(&dets);
		return (EXIT_SUCCESS);
	}
	else
		philoproc(&dets);
}
