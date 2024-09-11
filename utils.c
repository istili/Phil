#include "philo.h"

void    destroy_forks(t_main *p, int indx)
{
    int i;

    i = 0;
	while (indx > i)
	{
		pthread_mutex_destroy(&p->forks[i]);
		i++;
	}
}

void    destroy_2(t_main *p, int indx)
{
    int i;

    i = 0;
	destroy_forks(p, p->n_philo);
	while (indx > i)
	{
		pthread_mutex_destroy(&p->arr[i].time_mutex);
		i++;
	}
}

void    destroy_3(t_main *p, int indx)
{
    int i;

    i = 0;
	destroy_2(p, p->n_philo);
	while (indx > i)
	{
		pthread_mutex_destroy(&p->arr[i].meals_mutex);
        i++;
	}
}

void    ft_destroy(t_main *p, int i, int j, int indx)
{
    if (i == 0)
        free(p->forks);
    if (i == 1 && j == 0)
        pthread_mutex_destroy(&p->int_mutex);
    if (i == 2 && j == 0)
    {
        pthread_mutex_destroy(&p->int_mutex);
        pthread_mutex_destroy(&p->print_mutex);
    }
    if (i == 3 && j == 1)
    {
        pthread_mutex_destroy(&p->int_mutex);
        pthread_mutex_destroy(&p->print_mutex);
        destroy_forks(p, indx);
    }
    if (i == 3 && j == 2)
    {
        pthread_mutex_destroy(&p->int_mutex);
        pthread_mutex_destroy(&p->print_mutex);
        destroy_2(p, indx);
    }
    if (i == 3 && j == 3)
    {
        pthread_mutex_destroy(&p->int_mutex);
        pthread_mutex_destroy(&p->print_mutex);
        destroy_3(p, indx);
    }
    if (i != 0)
    {
        free(p->forks);
        free(p->arr);
    }
}
