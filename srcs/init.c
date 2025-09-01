/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:39:55 by lgerard           #+#    #+#             */
/*   Updated: 2025/09/02 00:41:09 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_mut_tab(pthread_mutex_t mut[], int *imut, t_sup *s)
{
	int	i;

	i = 0;
	while (i < (s->par[0] + 1))
	{
		if (pthread_mutex_init(&mut[i], NULL) == 0)
			imut[i] = 1;
		else
		{
			destroy_mut(s);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_mut_one(pthread_mutex_t *mut, int *imut, t_sup *s)
{
	if (pthread_mutex_init(mut, NULL) == 0)
		(*imut) = 1;
	else
	{
		destroy_mut(s);
		return (1);
	}
	return (0);
}

static int	init_sup_0(t_sup *s, int i)
{
	while (i < N_PHILO)
		s->imut_lastmeal[i++] = 0;
	i = 0;
	while (i < N_PHILO)
		s->imut_nmeal[i++] = 0;
	if (init_mut_tab(s->mut_f, s->imut_f, s) != 0)
		return (1);
	if (init_mut_tab(s->mut_lastmeal, s->imut_lastmeal, s) != 0)
		return (1);
	if (init_mut_tab(s->mut_nmeal, s->imut_nmeal, s) != 0)
		return (1);
	if (init_mut_one(&s->mut_end, &s->imut_end, s) != 0)
		return (1);
	if (init_mut_one(&s->mut_write, &s->imut_write, s) != 0)
		return (1);
	if (init_mut_one(&s->mut_start, &s->imut_start, s) != 0)
		return (1);
	return (0);
}

int	init_sup(t_sup *s, int i)
{
	while (i < N_PHILO)
		s->threads[i++] = 0;
	i = 0;
	while (i < N_PHILO)
		s->ids[i++] = NULL;
	s->start_ms = -1;
	i = 0;
	while (i < N_PHILO)
		s->lastmeal[i++] = 0;
	i = 0;
	while (i < N_PHILO)
		s->nmeal[i++] = s->par[4];
	i = 0;
	while (i < N_PHILO)
		s->forks[i++] = 0;
	i = 0;
	while (i < N_PHILO)
		s->imut_f[i++] = 0;
	s->imut_start = 0;
	s->end = 0;
	s->imut_start = 0;
	s->imut_end = 0;
	s->imut_write = 0;
	return (init_sup_0(s, 0));
}
