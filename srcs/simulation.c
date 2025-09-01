/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:18:33 by lgerard           #+#    #+#             */
/*   Updated: 2025/09/02 00:41:29 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_tab(t_sup *s, int i)
{
	t_tab	*t;

	t = malloc(sizeof(t_tab));
	if (!t)
		return (1);
	s->ids[i] = t;
	t->id = i;
	t->par = s->par;
	t->start_ms = &s->start_ms;
	t->lastmeal = &s->lastmeal[i];
	t->nmeal = &s->nmeal[i];
	t->rfork = &s->forks[i];
	t->lfork = &s->forks[(i % (s->par[0])) + 1];
	t->end = &s->end;
	t->mut_rf = &s->mut_f[i];
	t->mut_lf = &s->mut_f[(i % (s->par[0])) + 1];
	t->mut_lastmeal = &s->mut_lastmeal[i];
	t->mut_nmeal = &s->mut_nmeal[i];
	t->mut_start = &s->mut_start;
	t->mut_end = &s->mut_end;
	t->mut_write = &s->mut_write;
	return (0);
}

static int	failed_thread(t_sup *s, int i)
{
	pthread_mutex_lock(&s->mut_end);
	s->end = 1;
	pthread_mutex_unlock(&s->mut_end);
	printf("Failed to create thread philosopher\n");
	while (i < (s->par[0] + 1) && s->threads[i] != 0)
	{
		if (pthread_join(s->threads[i], NULL) != 0)
			printf("Failed to join thread %i\n", i);
		i++;
	}
	return (release_all(s, -1, 1));
}

static int	start_sim_0(t_sup *s, int i)
{
	long long	k;

	k = get_time_ms();
	while (i < s->par[0] + 1)
	{
		pthread_mutex_lock(&s->mut_lastmeal[i]);
		s->lastmeal[i] = k;
		pthread_mutex_unlock(&s->mut_lastmeal[i]);
		i++;
	}
	pthread_mutex_lock(&s->mut_start);
	s->start_ms = k;
	pthread_mutex_unlock(&s->mut_start);
	i = 0;
	while (i < s->par[0] + 1)
	{
		if (pthread_join(s->threads[i], NULL) != 0)
		{
			printf("Failed to join thread %i\n", i);
			return (release_all(s, -1, 1));
		}
		i++;
	}
	return (release_all(s, -1, 0));
}

int	start_sim(t_sup *s, int i)
{
	while (i < (s->par[0] + 1))
	{
		if (philo_tab(s, i) != 0)
		{
			printf ("Philosopher memory allocation issue\n");
			return (release_all(s, i, 1));
		}
		i++;
	}
	i = 0;
	if (pthread_create(&s->threads[i], NULL, supervisor, (void *)s) != 0)
	{
		printf("Failed to create thread supervisor\n");
		return (release_all(s, -1, 1));
	}
	i++;
	while (i < (s->par[0] + 1))
	{
		if (pthread_create(&s->threads[i], NULL, phil, (void *)s->ids[i]) != 0)
			return (failed_thread(s, 0));
		i++;
	}
	return (start_sim_0(s, 0));
}
