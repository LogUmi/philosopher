/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:35:35 by lgerard           #+#    #+#             */
/*   Updated: 2025/09/02 00:41:39 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	long	val;
	long	sign;

	i = 0;
	val = 0;
	sign = 1;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		val = (val * 10);
		val = val + (nptr[i] - 48);
		i++;
	}
	val = val * sign;
	if (!(val >= INT_MIN && val <= INT_MAX))
		return (-1);
	return (val);
}

long long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000LL) + (time.tv_usec / 1000));
}

static int	ins_num(char *s, long long n, int i)
{
	int	j;

	j = 0;
	if (n >= 10)
	{
		j = ins_num(s, n / 10, i);
		s[i + j] = n % 10 + 48;
	}
	if (n < 10)
		s[i] = n + 48;
	return (j + 1);
}

long long	get_pmsg(t_tab *t, char *msg, int i, int j)
{
	long long	k;
	long long	l;
	char		c[100];

	k = get_time_ms();
	l = k - (*t->start_ms);
	i += ins_num(&c[0], l, 0);
	c[i++] = 32;
	i += ins_num(&c[0], (long long)t->id, i);
	c[i++] = 32;
	while (msg[j])
		c[i++] = msg[j++];
	c[i] = 0;
	pthread_mutex_lock(t->mut_write);
	write(1, &c[0], i);
	pthread_mutex_unlock(t->mut_write);
	return (k);
}

long long	get_smsg(t_sup *s, int id, char *msg, int i)
{
	long long	k;
	long long	l;
	char		c[100];
	int			j;

	j = 0;
	k = get_time_ms();
	l = k - s->start_ms;
	i += ins_num(&c[0], l, 0);
	c[i++] = 32;
	i += ins_num(&c[0], (long long)id, i);
	c[i++] = 32;
	while (msg[j])
		c[i++] = msg[j++];
	c[i] = 0;
	pthread_mutex_lock(&s->mut_write);
	write(1, &c[0], i);
	pthread_mutex_unlock(&s->mut_write);
	return (k);
}
