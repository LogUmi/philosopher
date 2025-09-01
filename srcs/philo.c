/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:30:34 by lgerard           #+#    #+#             */
/*   Updated: 2025/09/02 00:41:20 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_values(t_sup *s)
{
	if (s->par[0] == 0 || s->par[0] > (N_PHILO - 1))
	{
		printf("Wrong number of philosophers (must be between 1 up to ");
		printf("%i/n", N_PHILO - 1);
		return (1);
	}
	if (s->par[4] == 0)
	{
		printf("number_of_times_each_philosopher_must_eat must be > 0\n");
		return (1);
	}
	return (0);
}

static int	ispdigit(char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0 && s[i] == '+')
		i++;
	if (i > 1)
		return (-1);
	while (s[i] != 0 && s[i] >= '0' && s[i] <= '9')
		i++;
	if (i == 0 || (s[0] == '+' && i < 2))
		return (-1);
	if (s[i] != 0)
		return (-1);
	return (ft_atoi(s));
}

static int	error_arg(void)
{
	printf("arguments error: please type only int positives digitals ");
	printf("arguments:\n number_of_philosophers  time_to_die(ms)  ");
	printf("time_to_eat(ms)  time_to_sleep(ms) ");
	printf ("[number_of_times_each_philosopher_must_eat]\n");
	return (1);
}

int	main(int argc, char **argv)
{
	int		i;
	t_sup	s;

	i = 1;
	if (argc < 5)
		return (error_arg());
	else if (argc <= 6)
	{
		while (i < argc)
		{
			s.par[i - 1] = ispdigit(argv[i]);
			if (s.par[i - 1] == -1)
				return (error_arg());
			i++;
		}
	}
	else
		return (error_arg());
	if (argc == 5)
		s.par[4] = -1;
	if (check_values(&s) != 0)
		return (error_arg());
	if (init_sup(&s, 0) != 0)
		return (1);
	return (start_sim(&s, 1));
}
/* 
number_of_philosophers
time_to_die(ms)
time_to_eat(ms)
time_to_sleep(ms)
[number_of_times_each_philosopher_must_eat]
 */