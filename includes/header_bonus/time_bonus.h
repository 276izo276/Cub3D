#ifndef TIME_H
# define TIME_H

# include <sys/time.h>

typedef struct timeval	t_time;

long long				get_mtime(void);

#endif
