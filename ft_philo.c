#include "ft_philo.h"


int ft_init_philo_data(t_philo *philo, int argc, char const **argv)
{
    if (ft_check_arg(argv) == -1)
        return (1);
    if (argc < 5 || argc > 6)
        return (2);
    philo->num_philo = ft_atoi(argv[1]);
    if (philo->num_philo > 200 || philo->num_philo <= 0)
        return (3);
    philo->time_to_die = ft_atoi(argv[2]);
    if (philo->time_to_die <= 0)
        return (4);
    philo->time_to_eat = ft_atoi(argv[3]);
    philo->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        philo->must_each_eat = ft_atoi(argv[5]);
    return (0);
}

int check_status_and_write(t_philo *philo, int argc, char const **argv)
{
    if (ft_init_philo_data(philo, argc, argv) == 1)
        return(printf("Error: Found a invalid character\n"), -1);
    else if (ft_init_philo_data(philo, argc, argv) == 2)
        return(printf("Error: Invalid number of args\n"), -1);
    else if (ft_init_philo_data(philo, argc, argv) == 3)
        return(printf("Error: Number of philosophers is not valid\n"), -1);
    else if (ft_init_philo_data(philo, argc, argv) == 4)
        return(printf("Error: Time to die is not valid\n"), -1);
    return (0);
}

void ft_print_data(t_philo *philo, int argc)
{
    (void)argc;
    printf("num_philo: %d\ntime_to_die: %d\ntime_to_eat: %d\ntime_to_sleep: %d\n",
        philo->num_philo, philo->time_to_die, philo->time_to_eat, philo->time_to_sleep);
    if (argc == 6)
        printf("must_each_eat: %d\n", philo->must_each_eat);
}

int main(int argc, char const *argv[])
{
    t_philo philo;

    if (check_status_and_write(&philo, argc, argv) != 0)
        return (1);
    ft_print_data(&philo, argc);
    return 0;
}
