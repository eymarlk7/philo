#include "ft_philo.h"

int ft_check_arg(char **argv)
{
    int i;
    int j;

    i = 1;
    while (argv[i])
    {
        j = 0;
        while (argv[i][j])
        {
            if (argv[i][j] == '-')
                j++;
            if (!(argv[i][j] >= 48 && argv[i][j] <= 57))
                return (-1);
            j++;
        }
        i++;
    }
    return (0);
}

int ft_atoi(const char *nptr)
{
    int signal;
    int result;

    signal = 1;
    result = 0;
    while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
        nptr++;
    if (*nptr == 43 || *nptr == 45)
    {
        if (*nptr == 45)
            signal = -1;
        nptr++;
    }
    while (*nptr >= 48 && *nptr <= 57)
        result = result * 10 + (*nptr++ - '0');
    return (result * signal);
}

int check_status_and_write(t_data *data, int argc, char **argv)
{
    int check_val;
    
    check_val = ft_ini_data(data, argc, argv);
    if (check_val == 1)
        return(printf("Error: Found an invalid character\n"), -1);
    else if (check_val == 2)
        return(printf("Error: Invalid number of arguments\n"), -1);
    else if (check_val == 3)
        return(printf("Error: Number of philosophers is not valid\n"), -1);
    else if (check_val == 4)
        return(printf("Error: Time to die is not valid\n"), -1);
    return (0);
}