#!/bin/bash
echo "Entrez le nombre de philosophes :"
read num_philosophers
echo "Entrez time_to_die :"
read time_to_die
echo "Entrez time_to_eat :"
read time_to_eat
echo "Entrez time_to_sleep :"
read time_to_sleep
echo "Entrez meal_number :"
read meal_number
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./philo $num_philosophers $time_to_die $time_to_eat $time_to_sleep $meal_number
