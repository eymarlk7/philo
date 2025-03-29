#include "philo.h"

//check if the character is a number
int	ft_isdigit(int c)
{
    return (c >= 48 && c <= 57);
}

//convert a character number of type string for a int type
int	ft_atoi(char *ptr)
{
	int	signal;
	int	result;
	
	signal = 1;
	result = 0;
	while (*ptr == 32 || (*ptr >= 9 && *ptr <= 13))
		ptr++;
	if (*ptr == 43 || *ptr == 45)
	{
		if (*ptr == 45)
			signal = -1;
		ptr++;
	}
	while (ft_isdigit(*ptr))
	{
		result = result * 10 + (*ptr - '0');
		ptr++;
	}
	return (result * signal);
}

//get time in ms
//I need to understand how this function works.
size_t	get_cur_time(void)
{
	struct timeval  time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

size_t	ft_usleep(size_t time_ms)
{
	size_t	start;

	start = get_cur_time();
	while ((get_cur_time() - start) < time_ms)
		usleep(1000);
	return (0);
}