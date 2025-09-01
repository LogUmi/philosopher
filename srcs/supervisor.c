/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:35:17 by lgerard           #+#    #+#             */
/*   Updated: 2025/09/02 00:41:33 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*died_philo(t_sup *s, int i)
{
	pthread_mutex_lock(&s->mut_end);
	s->end = 1;
	pthread_mutex_unlock(&s->mut_end);
	usleep(1000);
	get_smsg(s, i, "died\n", 0);
	return (NULL);
}

static void	*nmeal_reach(t_sup *s)
{
	pthread_mutex_lock(&s->mut_end);
	s->end = 1;
	pthread_mutex_unlock(&s->mut_end);
	usleep(1000);
	get_smsg(s, s->par[4], "meal(s) taken for all\n", 0);
	return (NULL);
}

void	*supervisor(void *arg)
{
	t_sup	*s;
	int		i;
	int		j;

	s = (t_sup *)arg;
	j = 0;
	while (is_start(s, NULL) == -1 && is_end(s, NULL) == 0)
		usleep(200);
	while (1)
	{
		usleep(6000);
		i = 1;
		j = 0;
		while (i < (s->par[0] + 1))
		{
			j = j + is_nmeal(s, i);
			if ((get_time_ms() - is_lastmeal(s, i)) > s->par[1])
				return (died_philo(s, i));
			i++;
		}
		if (j == 0)
			return (nmeal_reach(s));
	}
	return (NULL);
}
