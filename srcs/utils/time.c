#include "time.h"
#include <stdlib.h>

long long	get_mtime(void)
{
	t_time	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
