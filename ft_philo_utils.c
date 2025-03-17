#include "ft_philo.h"

int ft_check_arg(char const **argv)
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